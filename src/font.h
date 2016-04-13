#pragma once

namespace cj {

#ifdef OS_LINUX
#define HFONT int
#endif

class Font : public Object
{
public:
	int id;//Идентификатор шрифта
	int width;//Ширина шрифта
	int height;//Высота шрифта
	bool w;//Толстый
	bool i;//Наклонённый
	bool u;//Подчёркнутый
	bool s;//Перечёркнутый
	bool d3;//Трёхмерный
	String fontName;//Имя шрифта
	HFONT hFont;
	Font();//Конструктор
	void set(int width, int height, bool w, bool i, bool u, bool s, bool d3, String fontName, String name);
	//Установить параметры шрифта
	bool compare(Font *fnt);//Сверить с другим шрифтом
};
class FontManager : public Object
//Менеджер шрифтов
{
public:
	List lstFont;//Список шрифтов
	FontManager();//Конструктор
	Font* getFont(String value);//Найти шрифт по имени
	Font* getFont(int id);//Получить шрифт по id
	int getId(Font* value);//Получить идентификатор по шрифту
	int getId(String value);//Получить идентификатор шрифта по имени
};

}

