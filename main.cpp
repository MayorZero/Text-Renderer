int main()
{
 ...Window and open gl stuff
 
 Renderer2D renderer;
 renderer.Create();
 
 Test* test = new Test(renderer);
 
 bool running = true;
 while(running)
 {
  ...Event stuff
  
  renderer.Begin();
  test->Draw();
  renderer.Present();
  
  ...Swap buffers
 }
}
