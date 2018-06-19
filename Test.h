class Test
{
public:
  Test(Renderer2D* renderer2D);
  ~Test();
  
  void Draw();
  
private:
  Renderer2D* m_renderer;
};
