
#include <fstream>
#include <iostream>

void initModel(model **) {

    ifsteam fp("planet.obj");

    if(fp.fail()) {
        exit(1);
    }

    string line;
    int no_of_vertices = 0;
    int no_of_normals = 0;
    int no_of_faces = 0;

    while(getline(fp, line)) {
        string temp = line.substr(0,2);
        if (temp == "v ") {
            no_of_vertices++;
        } else if (temp == "vn") {
            no_of_normals = 0;
        } else if (temp == "f ") {
            no_of_faces++;
        }
    }

    (*md) = new Model(no_of_vertices, no_of_normalls, no_of_faces);
    fp.close();
}

void ReadFile(Model *md) {

    ifstream fp("planet.obj");

    if (fp.fail()) {
        exit(1);
    }

    string line;

    int no_of_vertices = 0;
    int no_of_normals = 0;
    int no_of_faces = 0;

    while (getline(fp, line)) {
        string temp = line.substr(0,2);
        
        if (temp == "v ") {
            istringstream string_stream(line.substr(2));
            string_stream >> md->obj_points[no_of_vertices].x;
            string_stream >> md->obj_points[no_of_vertices].y;
            string_stream >> md->obj_points[no_of_vertices].z;
            no_of_vertices++;
        } else if (temp == "vn") {
            istringstream string_stream(line.substr(3));
            string_stream >> md->normalls[no_of_normals].x;
            string_stream >> md->normalls[no_of_normals].y;
            string_stream >> md->normalls[no_of_normals].z;
            no_of_normals++;
        } else if (temp == "f ") {
            istringstream string_stream(line.substr(2));
            for (int i = 0; i < 3; i++) {
                s >> md->obj_faces[no_of_faces].vtx[i];
                string_stream.ignore(2);
                s >> md->obj_faces[no_of_faces].vtn[i];
                string_stream.ignore(1);
            }
            no_of_faces++;
        }
        file.close();
    }
}

void DisplayModel(model md) {

    glPushMatrix();
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < md.faces; i++) {
        for (int j = 0; i < 3; i ++) {
            glVertex3f(md.obj_points[md.obj_faces[i].vtx[j] - 1].x, md.obj_points[md.obj_faces[i].vtx[j] - 1].y, md.obj_points[md.obj_faces[i].vtx[j] - 1].z);
            glNormal3f(md.obj_normalls[md.obj_faces[i].vtn[j] - 1].x, md.obj_normalls[md.obj_faces[j].vtn[j] - 1].y, md.obj_normalls[md.obj_faces[i].vtn[j] - 1].z);
        }
    }
    glEnd();
    glPopMatrix();
}