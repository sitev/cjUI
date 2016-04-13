#pragma once

namespace cj {

#ifdef OS_LINUX
#define HFONT int
#endif

class Font : public Object
{
public:
	int id;//������������� ������
	int width;//������ ������
	int height;//������ ������
	bool w;//�������
	bool i;//����������
	bool u;//������������
	bool s;//�������������
	bool d3;//���������
	String fontName;//��� ������
	HFONT hFont;
	Font();//�����������
	void set(int width, int height, bool w, bool i, bool u, bool s, bool d3, String fontName, String name);
	//���������� ��������� ������
	bool compare(Font *fnt);//������� � ������ �������
};
class FontManager : public Object
//�������� �������
{
public:
	List lstFont;//������ �������
	FontManager();//�����������
	Font* getFont(String value);//����� ����� �� �����
	Font* getFont(int id);//�������� ����� �� id
	int getId(Font* value);//�������� ������������� �� ������
	int getId(String value);//�������� ������������� ������ �� �����
};

}

