#include "ViewerTexture.h"

ViewerTexture::ViewerTexture()
{
}


ViewerTexture::~ViewerTexture()
{
}

// �ؽ��� �ҷ�����
void ViewerTexture::LoadTexture(std::string directory, int screen_width)
{
	SDL_Surface *surface;
	GLuint textureID;
	int mode;
	directory += "menu.bmp";

	surface = SDL_LoadBMP(directory.c_str());
	if (surface)
	{
		if (surface->format->BytesPerPixel == 3 || 
			surface->format->BytesPerPixel == 4)
		{
			if (surface->format->BytesPerPixel == 3)
			{
				mode = GL_RGB;
			}
			else if (surface->format->BytesPerPixel == 4)
			{
				mode = GL_RGBA;
			}

			this->width = surface->w;
			this->height = surface->h;

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			SDL_FreeSurface(surface);
			this->textureID = textureID;
		}
		else
		{
			SDL_FreeSurface(surface);
		}
	}	
}

// �ؽ��� �׸���
void ViewerTexture::DrawTexture(int x, int y)
{
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	{
		glTexCoord2i(0, 1);
		glVertex3i(x, y, 0);

		glTexCoord2i(1, 1);
		glVertex3i(x + this->width, y, 0);

		glTexCoord2i(1, 0);
		glVertex3i(x + this->width, y + this->height, 0);

		glTexCoord2i(0, 0);
		glVertex3i(x, y + this->height, 0);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	this->x1 = x;
	this->x2 = x + this->width;
	this->y1 = y;
	this->y2 = y + this->height;
}

// �ؽ��� ID ����
void ViewerTexture::SetTextureID(GLint textureID)
{ 
	this->textureID = textureID; 
}

// �ؽ��� �ʺ� ����
void ViewerTexture::SetWidth(int width) 
{ 
	this->width = width;
}

// �ؽ��� ���� ����
void ViewerTexture::SetHeight(int height) 
{ 
	this->height = height; 
}

// �ؽ��� X ������ ����
void ViewerTexture::SetX1(int x1) 
{ 
	this->x1 = x1;
}

// �ؽ��� X ������ ����
void ViewerTexture::SetX2(int x2)
{ 
	this->x2 = x2;
}

// �ؽ��� Y ������ ����
void ViewerTexture::SetY1(int y1)
{ 
	this->y1 = y1;
}

// �ؽ��� Y ������ ����
void ViewerTexture::SetY2(int y2) 
{
	this->y2 = y2;
}

// �ؽ��� ID �޾ƿ���
GLint ViewerTexture::GetTextureID() 
{
	return this->textureID;
}

// �ؽ��� �ʺ� �޾ƿ���
int ViewerTexture::GetWidth()
{ 
	return this->width;
}

//�ؽ��� ���� �޾ƿ���
int ViewerTexture::GetHeight()
{
	return this->height;
}

// �ؽ��� X ������ �޾ƿ���
int ViewerTexture::GetX1()
{
	return this->x1;
}

// �ؽ��� X ������ �޾ƿ���
int ViewerTexture::GetX2() 
{ 
	return this->x2;
}

// �ؽ��� Y ������ �޾ƿ���
int ViewerTexture::GetY1()
{
	return this->y1; 
}

// �ؽ��� Y ������ �޾ƿ���
int ViewerTexture::GetY2()
{ 
	return this->y2; 
}
