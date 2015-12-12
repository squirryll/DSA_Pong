#include "GameObject.h"

GameObject::GameObject(string filename, vec3 pos)
{
	velocity = vec3(0);
	position = pos;
	verts = loadOBJVerts(filename);
	elements = loadOBJElements(filename);
}

vector<vert> GameObject::loadOBJVerts(string filename)
{
	vector<vec3> positions;
	vector<vec2> uvs;
	vector<vec3> normals;
	ifstream file(filename);

	string line;
	while (getline(file, line))
	{
		istringstream iss = istringstream(line);
		string head;
		float x, y, z;
		iss >> head;
		if (head == "v")
		{
			iss >> x >> y >> z;
			positions.push_back(vec3(x, y, z));
		}
		else if (head == "vt")
		{
			iss >> x >> y;
			uvs.push_back(vec2(x, y));
		}
		else if (head == "vn")
		{
			iss >> x >> y >> z;
			normals.push_back(vec3(x, y, z));
		}
	}

	vector<vert> verts;
	for (unsigned int i = 0; i < positions.size(); i++) {
		vert newVert = { positions[i], uvs[i], normals[i] };
		verts.push_back(newVert);
	}
	return verts;
}

// Load in our face data from the text file.
// Returns a vector of shorts, which we use for the element buffer.
vector<unsigned short> GameObject::loadOBJElements(string filename)
{
	ifstream file(filename);
	vector<unsigned short> faces;
	string line;
	while (getline(file, line))
	{
		istringstream iss = istringstream(line);
		string head, x, y, z;
		iss >> head;
		if (head == "f")
		{
			iss >> x >> y >> z;

			faces.push_back(((unsigned short)x[0] - '0') - 1);
			faces.push_back(((unsigned short)y[0] - '0') - 1);
			faces.push_back(((unsigned short)z[0] - '0') - 1);
		}
	}
	return faces;
}

void GameObject::setPos(vec3 pos)
{
	position = pos;
}

vec3 GameObject::getPos()
{
	return position;
}

vec3 GameObject::getVel()
{
	return velocity;
}

void GameObject::setVel(vec3 vel)
{
	velocity = vel;
}

vector<unsigned short> GameObject::getElems()
{
	return elements;
}

vector<vert> GameObject::getVerts()
{
	return verts;
}

GameObject::~GameObject()
{
}
