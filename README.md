# SDL_opengl
SDL with opengl.  
尝试加载模型、材质、光照研究等。
### 01. Environment With SDL With OpenGL: SDL2openGL 
### 02. Analysis Urho3D SourceCode then extract them
为了加载模型，尝试阅读Urho3D加载模型代码。并理解和实现:  
Urho3D 42_PBRMaterials 案例
```
SharedPtr<File> file = cache->GetFile("Scenes/PBRExample.xml"); // 加载场景文件, 包含了模型
scene_->LoadXML(*file); // 解析场景文件

Node* sphereWithDynamicMatNode = scene_->GetChild("SphereWithDynamicMat"); // 获取MDL模型
auto* staticModel = sphereWithDynamicMatNode->GetComponent<StaticModel>(); 
dynamicMaterial_ = staticModel->GetMaterial(0); // 获取模型上的材质
```
