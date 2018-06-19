class Texture
{
public:
  Texture() = default;
  virtual ~Texture() = default;

  Texture* Create(Uint width, Uint height) { return new GLTexture(width, height); }
  
  virtual void BindTexture(Uint slot = 0) {}
  virtual void UnbindTexture(Uint slot = 0) {}

  virtual void Free() {}

  virtual void setData(const void* pixels) {}

protected:
  Uint w = 0, 
       h = 0;
};

class GLTexture : public Texture
{
public:
  GLTexture(Uint width, Uint height);
  ~GLTexture();

  void BindTexture(Uint slot = 0) override;
  void UnbindTexture(Uint slot = 0) override;

  virtual void setData(const void* pixels) override;

  void Free() override;

private:		
  std::string filePath;
  Uint texture = 0;

  Uint LoadFromFile();
};
