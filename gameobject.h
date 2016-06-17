class GameObject{
  public:
    Vector3* pos;
    Vector3* rot;
    Vector3* mov;
    Vector3* ang_mov;

    GameObject(Vector3* a);
    void update();
    void draw();
};
