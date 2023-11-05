#ifndef __MODEL__LOADER__
#define __MODEL__LOADER__

#include "Mesh.h"

/**
 * Factory class that loads a mesh / model from a file and then will return copies of that mesh 
*/
class ModelLoader {
    public: 
        Mesh loadModelFromFile();
    private:

}

#endif