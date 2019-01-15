

struct point {

	float x;
	float y;
	float z;
};

struct normal {

	float x;
	float y;
	float z;
};

struct face {

	int vtx[3];
	int vtn[3];
};

struct model {

	point *obj_points;
	normal *obj_normals;
	face *obj_faces;

	int vertices;
	int normals;
	int faces;

	model(int a, int b, int c) {

		obj_points = new point[a];
		obj_normals = new normal[b];
		obj_faces = new face[c];

		vertices = a;
		normals = b;
		faces = c;
	}

	~model() {
		delete obj_points;
		delete obj_normals;
		delete obj_faces;
	}
};

//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();
void initModel(model **md);
void ReadFile(model *md);
void DisplayModel(model *md);
void Keyboard(unsigned char key, int x, int y);

