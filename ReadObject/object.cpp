#include "object.h"
#include <string>
#include <stdlib.h>

extern GLuint texture[5];

void Object::readObj(string filename)
{
	string line, type, mtllib, mtlname;
	ifstream fin(filename);
	istringstream is;
	GLdouble minX = 0, minY = 0, minZ = 0;

	if (!fin) {
		cout << "Cannot open the file when ReadObj:" << filename << endl;
		exit(0);
	}
	while (!fin.eof())
	{
		is.clear();
		getline(fin, line);
		if (line.size() == 0 || line[0] == '#' || line[0] == 's')
			continue;
		is.str(line.c_str());
		is >> type;
		//存储mtl文件名称
		if (type == "mtllib") {
			is >> mtllib;
		}
		//存储材质名称
		else if (type == "usemtl") {
			is >> mtlname;
			materials.push_back(mtlname);
		}
		//存储点坐标
		else if (type == "v") {
			vertex v;
			is >> v.x >> v.y >> v.z;
			minX = (minX < v.x) ? v.x : minX;
			minY = (minY < v.y) ? v.y : minY;
			minZ = (minZ < v.z) ? v.z : minZ;
			vertices.push_back(v);
		}
		//存储法向量
		else if (type == "vn") {
			vertex vn;
			is >> vn.x >> vn.y >> vn.z;
			normals.push_back(vn);
		}
		//存储纹理坐标
		else if (type == "vt") {
			pair<float, float>vt;
			is >> vt.first >> vt.second;
			texturecoords.push_back(vt);
		}
		//新的一块
		else if (type == "g" || type == "o") {
			pair<int, int> rc;
			rc.second = 0;
			row_col.push_back(rc);
			continue;
		}
		//存储面信息
		else if (type == "f") {
			int r = 0, c = 0;
			while (is >> type) {
				c = count(type.begin(), type.end(), '/');
				switch (c) {
				case 0:
					faces.push_back(atoi(type.c_str()));
					break;
				case 1:
					faces.push_back(atoi(string(type.begin(), type.begin() + type.find("/")).c_str()));
					faces.push_back(atoi(string(type.begin() + type.find("/") + 1, type.end()).c_str()));
					break;
				case 2:
					int a1 = type.find("/");
					int a2 = type.find("/", a1 + 1);
					faces.push_back(atoi(string(type.begin(), type.begin() + a1).c_str()));
					faces.push_back(atoi(string(type.begin() + a1 + 1, type.begin() + a2).c_str()));
					faces.push_back(atoi(string(type.begin() + a2 + 1, type.end()).c_str()));
					break;
				}
				++r;
			}
			//f 286/540/182 283/535/182 285/538/182 287/541/182 
			//col=3,row=4
			pair<int, int> rc;
			rc.first = r;
			rc.second = c + 1;
			row_col.push_back(rc);
		}
		line = "";
	}
	std::cout << minX << " " << minY << " " << minZ << "\n";
	readMTL(mtllib);
}

void Object::readMTL(string filename) {
	string line, type, name = "";
	ifstream fin(filename);
	istringstream is;
	Material m;

	if (!fin) {
		cout << "Cannot open the file when ReadObj:" << filename << endl;
		return;
	}
	while (!fin.eof())
	{
		is.clear();
		getline(fin, line);
		if (line.size() == 0 || line[0] == '#')
			continue;
		is.str(line.c_str());
		is >> type;
		if (type == "newmtl") {
			if (!name.empty())
				matMap.insert(make_pair(name, m));
			is >> name;
			m.clear();
		}
		//读取环境光参数
		if (type == "Ka") {
			is >> m.ambient[0] >> m.ambient[1] >> m.ambient[2];
			//m.ambient[3] = 1.0;
		}
		//读取漫反射参数
		if (type == "Kd") {
			is >> m.diffuse[0] >> m.diffuse[1] >> m.diffuse[2];
			//m.diffuse[3] = 1.0;
		}
		//读取镜面反射参数
		if (type == "Ks") {
			is >> m.specular[0] >> m.specular[1] >> m.specular[2];
			//m.specular[3] = 1.0;
		}
		if (type == "Ke") {
			is >> m.emission[0] >> m.emission[1] >> m.emission[2];
			//m.emission[3] = 1.0;
		}
		if (type == "map_Ka") {
			string fname;
			is >> fname;
			m.map = load_texture(fname.c_str());
		}
	}
	if (!name.empty())
		matMap.insert(make_pair(name, m));
}

void Object::setMaterial(Material &mat)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat.emission);
	glMaterialf(GL_FRONT, GL_SHININESS, 100);
}

void Object::draw() {
	int row, col;
	vector<pair<int, int>>::iterator rc;
	vector<int>::iterator iter = faces.begin();
	vector<string>::iterator matIter = materials.begin();
	glEnable(GL_TEXTURE_2D);
	//绑定纹理
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	for (rc = row_col.begin(); rc != row_col.end(); rc++) {
		row = (*rc).first;
		col = (*rc).second;

		if (col == 0)//新的一块
		{
			Material m = matMap[*matIter];
			setMaterial(m);
			if (m.map != -1) {
				glBindTexture(GL_TEXTURE_2D, m.map);
			}
			matIter++;
			continue;
		}
		int i = 0;
		//画三角形
		if (row == 3) {
			glBegin(GL_TRIANGLES);
		}
		else if (row == 4) {
			glBegin(GL_QUADS);
		}
		else {
			glBegin(GL_POLYGON);
		}
		while (iter != faces.end() && i < row)
		{
			if (col == 3) {
				glNormal3f(normals[*(iter + 2) - 1].x, normals[*(iter + 2) - 1].y, normals[*(iter + 2) - 1].z);
			}
			glTexCoord2f(texturecoords[*(iter + 1) - 1].first, texturecoords[*(iter + 1) - 1].second);
			glVertex3f(vertices[*iter - 1].x, vertices[*iter - 1].y, vertices[*iter - 1].z);
			iter += col;
			i++;
		}
		//glBindTexture(GL_TEXTURE_2D, 0);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

inline int power_of_two(int n)
{
	if (n <= 0) return 0;
	return (n&(n - 1)) == 0;
}

GLuint Object::load_texture(const char *file_name)
{
	GLint width, height, total_bytes;
	GLuint last_texture_ID, texture_ID = 0;
	GLubyte *pixels = NULL;
	FILE *pFile;

	if ((pFile = fopen(file_name, "rb")) == NULL)
	{
		cout << "Read texture error" << endl;
		return 0;
	}

	fseek(pFile, 18, SEEK_SET);
	fread(&width, sizeof(width), 1, pFile);
	fread(&height, sizeof(height), 1, pFile);
	fseek(pFile, 54, SEEK_SET);

	total_bytes = (width * 3 + (4 - width * 3 % 4) % 4)*height;

	if ((pixels = (GLubyte *)malloc(total_bytes)) == NULL)
	{
		fclose(pFile);
		return 0;
	}

	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width) || !power_of_two(height) || width>max || height>max)
		{
			const GLint new_width = 1024;
			const GLint new_height = 1024;
			GLint new_total_bytes;
			GLubyte *new_pixels = NULL;

			new_total_bytes = (new_width * 3 + (4 - new_width * 3 % 4) % 4)*new_height;
			new_pixels = (GLubyte *)malloc(new_total_bytes);
			if (new_pixels == NULL)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			gluScaleImage(GL_RGB, width, height, GL_UNSIGNED_BYTE, pixels, new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	free(pixels);
	fclose(pFile);
	return texture_ID;
}