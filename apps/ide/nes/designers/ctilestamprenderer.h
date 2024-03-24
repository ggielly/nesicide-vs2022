#ifndef CTILESTAMPRENDERER_H
#define CTILESTAMPRENDERER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class CTileStampRenderer : public QOpenGLWidget
{
public:
	CTileStampRenderer(QWidget* parent, char* data);
	~CTileStampRenderer() override;
	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void changeZoom(int newZoom);
	void setSize(int newX, int newY);
	bool pointToPixel(int ptx, int pty, int* pixx, int* pixy);
	void setBGColor(QColor clr);
	void setScrollX(int newScrollX) { scrollX = newScrollX; }
	void setScrollY(int newScrollY) { scrollY = newScrollY; }
	void setGrid(bool enabled) { gridEnabled = enabled; }

	void setBox(int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1)
	{
		boxX1 = x1;
		boxY1 = y1;
		boxX2 = x2;
		boxY2 = y2;
	}

	void getBox(int* x1, int* y1, int* x2, int* y2)
	{
		(*x1) = boxX1;
		(*y1) = boxY1;
		(*x2) = boxX2;
		(*y2) = boxY2;
	}

protected:
	void DeleteFunctions()
	{
		delete(m_pFunctions);
		m_pFunctions = nullptr;
	}

	QOpenGLFunctions* m_pFunctions = nullptr;
	int xSize;
	int ySize;
	int zoom;
	int scrollX;
	int scrollY;
	char* imageData;
	GLuint textureID;

	// Properties.
	bool gridEnabled;
	int boxX1;
	int boxY1;
	int boxX2;
	int boxY2;
	bool initialized;
};

#endif // CTILESTAMPRENDERER_H
