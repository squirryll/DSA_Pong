#include <Mesh.h>

Mesh::Mesh()
{

}
Mesh::Mesh(string filename)
{
	vector<vec3> positions;
	vector<vec2> uvs;
	vector<vec3> normals;
	vector<unsigned short> faces;
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
		else if (head == "f")
		{
			string xS, yS, zS;
			iss >> xS >> yS >> zS;
			faces.push_back(((unsigned short)xS[0] - '0') - 1);
			faces.push_back(((unsigned short)yS[0] - '0') - 1);
			faces.push_back(((unsigned short)zS[0] - '0') - 1);
		}
	}

	vector<vert> verts;
	for (unsigned int i = 0; i < positions.size(); i++) {
		vert newVert = { positions[i], uvs[i], normals[i] };
		verts.push_back(newVert);
	}

	Mesh(verts, faces);
}
Mesh::Mesh(const vector<vert> &verts, const vector<unsigned short> &elements)
{
	int vertBufSize = sizeof(vert) * verts.size();
	int elBufSize = sizeof(GLushort)*elements.size();
	numElements = elements.size();

	// Upload data.
	glBufferData(GL_ARRAY_BUFFER, vertBufSize, &verts[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elBufSize, &elements[0], GL_STATIC_DRAW);
}
Mesh::~Mesh()
{

}
void Mesh::draw()
{
	// Rebinding this shape's vaoIndex is needed if drawing more than one shape.
	glBindVertexArray(vaoIndex);
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, (void *)0);
}

void Mesh::setVaoIndex(GLuint vao)
{
	vaoIndex = vao;
}
