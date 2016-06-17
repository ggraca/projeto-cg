class Camera{
  public:
    Vector3* pos;
    Vector3* dir;
    Camera(Vector3* a, Vector3* b);
    void update();
};
