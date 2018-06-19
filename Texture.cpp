GLTexture::GLTexture(Uint width, Uint height)
{
  w = width;
  h = height;

  m_texture = LoadFromFile();
}

GLTexture::~GLTexture()
{
  Free();
}

Uint GLTexture::LoadFromFile()
{
  Uint tex = 0;

  glCall(glGenTextures(1, &tex));
  glCall(glBindTexture(GL_TEXTURE_2D, tex));

  glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr));

  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

  glCall(glGenerateMipmap(GL_TEXTURE_2D));

  glCall(glBindTexture(GL_TEXTURE_2D, 0));

  return tex;
}

void GLTexture::setData(const void* pixels)
{
  glCall(glBindTexture(GL_TEXTURE_2D, m_texture));
  glCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RED, GL_UNSIGNED_BYTE, pixels));
}

void GLTexture::Free()
{
  glCall(glDeleteTextures(1, &m_texture));
}

void GLTexture::BindTexture(Uint slot) 
{
  glCall(glActiveTexture(GL_TEXTURE0 + slot));
  glCall(glBindTexture(GL_TEXTURE_2D, m_texture));
}

void GLTexture::UnbindTexture(Uint slot) 
{
  glCall(glActiveTexture(GL_TEXTURE0 + slot));
  glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
