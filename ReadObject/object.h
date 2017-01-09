#pragma once
#include <GL/glut.h>
#include <math.h>
#include <memory.h>
#include <GL/glaux.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;
//顶点类
typedef struct
{
	float x;
	float y;
	float z;
}vertex;


class Material {
public:
	GLfloat ambient[3];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat emission[3];
	int map;
	void clear() {
		for (int i = 0; i < 3; i++) {
			ambient[i] = 0.0f;
			diffuse[i] = 0.0f;
			specular[i] = 0.0f;
			emission[i] = 0.0f;
		}
		map = -1;
	}
};

//物体类
class Object
{
	vector<vertex> vertices;//顶点
	vector<pair<float, float>>texturecoords;//纹理坐标
	vector<vertex>normals;//法向量
	vector<int>faces;//面
	vector<pair<int, int>>row_col;//面参数
	vector<string> materials;
private:
	map<string, Material> matMap;
	void readMTL(string filename);
	GLuint load_texture(const char *file_name);
	void setMaterial(Material &mat);
public:
	void readObj(string filename);
	void draw();
};

