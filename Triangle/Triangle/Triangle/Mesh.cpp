#include "Mesh.h"

Mesh::Mesh()
{
	// Raw tetrahedron data.
	// Positions, uvs and normals : one of each per vertex.
	vector<vec3> positions = {
		vec3(1, 1, 0),
		vec3(-1, 1, 0),
		vec3(0,-1, 0),
		vec3(0, 0,-1) };
	vector<vec2> uvs = {
		vec2(0, 0),
		vec2(0, 1),
		vec2(1, 0),
		vec2(1, 1) };
	vector<vec3> normals = {
		vec3(1, 1, 0),
		vec3(-1, 1, 0),
		vec3(1, -1, 0),
		vec3(0, 0, -1) };

	// Data is laced into a single collection, making uploading simpler and reading memory faster.
	vector<vert> verts;
	for (int i = 0; i < positions.size(); i++) {
		vert newVert = { positions[i], uvs[i], normals[i] };
		verts.push_back(newVert);
	}

	// Element array indicates that triangle 0 is made from vertices 0, 1 and 2.
	vector<unsigned short> elements = {
		0,1,2,
		0,2,3,
		0,3,1,
		3,2,1 };

	numElements = elements.size();
	Mesh(verts, elements);
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

	numElements = faces.size();
	Mesh(verts, faces);
}

Mesh::Mesh(const vector<vert> &verts, const vector<unsigned short> &elements)
{
	// Start uploading vertex data for this mesh and setting up per-vertex variables in the shader.
	int vertBufSize = sizeof(vert) * verts.size();
	int posStart = 0;
	int uvStart = sizeof(vec3);
	int normStart = sizeof(vec3) + sizeof(vec2);
	int stride = sizeof(vert);
	int elBufSize = sizeof(GLushort)*elements.size();
	int floatsPerVert = 8;

	// Generate buffers.
	glGenVertexArrays(1, &vaoIndex);
	GLuint vboIndex;
	glGenBuffers(1, &vboIndex);
	GLuint eboIndex;
	glGenBuffers(1, &eboIndex);

	// Bind buffers.
	glBindVertexArray(vaoIndex);
	glBindBuffer(GL_ARRAY_BUFFER, vboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboIndex);

	// Upload data.
	glBufferData(GL_ARRAY_BUFFER, vertBufSize, &verts[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elBufSize, &elements[0], GL_STATIC_DRAW);

	// Texture stuff.
	GLuint texID = SOIL_load_OGL_texture(
		"metal.jpg", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, texID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * floatsPerVert, (void*)(sizeof(GL_FLOAT) * 3));

	// Lighting stuff.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * floatsPerVert, 0);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * floatsPerVert, (void*)(sizeof(GL_FLOAT) * 5));

	// Describe (to shader's pos uv and norm) how data is packed.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(posStart));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(uvStart));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(normStart));
}

void Mesh::draw()
{
	// Rebinding this shape's vaoIndex is needed if drawing more than one shape.
	glBindVertexArray(vaoIndex);
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, (void *)0);
}