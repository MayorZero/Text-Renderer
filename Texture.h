class Texture
{
public:
  Texture() = default;
  virtual ~Texture() = default;

  Texture* Create(Uint width, Uint height);
  
  virtual void BindTexture(Uint slot = 0) {}
  virtual void UnbindTexture(Uint slot = 0) {}

  virtual void Free() {}

  virtual void setData(const void* pixels) {}

protected:
  Uint w = 0, 
       h = 0;
};
