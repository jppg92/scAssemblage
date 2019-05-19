#include "pointCloud.h"

//--------------------------------------------------------------
void pointCloud::addMesh( ofMesh * newMesh)
{
    // Acquire mesh vertices informations
    vector< glm::vec3 >  verts = newMesh->getVertices();
    vector <ofFloatColor> cols = newMesh->getColors();
    glm::vec3 centre = newMesh->getCentroid();
    
    //Translate mesh vertices to center
    for( int i = 0; i < verts.size(); i++)
    {
        verts[i] = glm::vec3( verts[i].x - centre.x,
                              verts[i].y  - centre.y,
                              verts[i].z  - centre.z);
    }
    
    // Rotate mesh vertices around axis using randomisation
    if(ofRandom(9) <= 3)
    {
        for( int i = 0; i < verts.size(); i++)
        {
            verts[i] = glm::vec3( verts[i].x,verts[i].y,verts[i].z);
            
        }
    } else if (ofRandom(9) >= 3 && ofRandom(1) <= 6 ) {
        
        for( int i = 0; i < verts.size(); i++)
        {
            verts[i] = glm::vec3( verts[i].y,verts[i].z,verts[i].x);
            
        }
        
    }else if (ofRandom(9) >= 6 ) {
            
            for( int i = 0; i < verts.size(); i++)
            {
                verts[i] = glm::vec3( verts[i].z,verts[i].x,verts[i].y);
                
            }
    }
    
    // AddVertices to "assembled" mesh
    mesh.addVertices( verts );
    mesh.addColors( cols);
}

//--------------------------------------------------------------
void pointCloud::draw()
{
    mesh.draw();
    mesh.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void pointCloud::save()
{
    // Save as ply to be read in Meshlab
    mesh.save("meshbin.ply",true);
}
