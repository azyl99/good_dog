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
//������
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

//������
class Object
{
	vector<vertex> vertices;//����
	vector<pair<float, float>>texturecoords;//��������
	vector<vertex>normals;//������
	vector<int>faces;//��
	vector<pair<int, int>>row_col;//�����
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

