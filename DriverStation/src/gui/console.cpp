#include "console.h"

Console::Console(){
	RectangleShape* back = new RectangleShape();
	back->setPosition(0.0f, 20.0f);
	back->setOutlineColor(Color::White);
	back->setOutlineThickness(1);
	addElem(back, ELEM_FUNC{
		RectangleShape* back = (RectangleShape*)ptr;
		Console* con = (Console*)par;
		Vector2f size = par->getSize();
		if (size != con->oldSize){
			con->oldSize = size;
			back->setSize(size - Vector2f(0.0f, 20.0f));
			con->rt.create((unsigned int)size.x, (unsigned int)size.y - 20);
			back->setTexture(&con->rt.getTexture());
		}
		con->rt.clear(Color(12, 12, 12));
		con->rt.draw(con->conTxt);
		con->rt.display();
	});

	Text* labelText = new Text();
	labelText->setFont(appRes->arial);
	labelText->setCharacterSize(20);
	labelText->setFillColor(Color::White);
	labelText->setString("Console");
	labelText->setPosition(5.0f, -5.0f);
	addElem(labelText, NULL);

	conTxt.setFont(appRes->arial);
	conTxt.setCharacterSize(16);
	conTxt.setFillColor(Color::White);
	conTxt.setString("This    ---- and more text to try and reach the end of the line. Turns out that a lot of text fits."
		"\nis\nsome\ntext\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nThe\nEnd");
	conTxt.setOrigin(-5.0f, -2.0f);
	//conTxt.setPosition(0.0f, -18.0f);
}

