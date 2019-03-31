class GameObject
{
private:
    float posx, posy, posz;
    char* name;
    char* texture;
    char* object_model;
    float vertex[];
public:
    GameObject();
    ~GameObject();
};

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
