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
		if(size != con->oldSize){
			con->oldSize = size;
			back->setSize(size - Vector2f(0.0f, 20.0f));
			con->rt.create((unsigned int)size.x, (unsigned int)size.y - 20);
			back->setTexture(&con->rt.getTexture(), true);
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
	conTxt.setString("This    ---- and more text to try and reach the end of the line. Turns out that a lot of text fits. T"
		"\nis\nsome\ntext\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nT\ni\ns\nt\nThe\nEnd");
	conTxt.setOrigin(-4.0f, -1.0f);
	//conTxt.setPosition(0.0f, -18.0f);
}


void Console::scroll(Event::MouseWheelScrollEvent event){
	Vector2u size = rt.getSize();
	FloatRect bounds = conTxt.getLocalBounds();
	if(event.wheel == Mouse::Wheel::VerticalWheel){
		conTxt.move(0.0f, event.delta*18.0f);
		Vector2f pos = conTxt.getPosition();
		if(event.delta > 0){
			if(pos.y > 0.0f)
				conTxt.setPosition(pos.x, 0.0f);
		} else {
			if(pos.y < size.y - bounds.height - 9.0f)
				conTxt.setPosition(pos.x, size.y - bounds.height - 9.0f);
		}
	} else {
		conTxt.move(event.delta*18.0f, 0.0f);
		Vector2f pos = conTxt.getPosition();
		if(event.delta > 0){
			if(pos.x > 0.0f)
				conTxt.setPosition(0.0f, pos.y);
		} else {
			if(pos.x < size.x - bounds.width - 9.0f)
				conTxt.setPosition(size.x - bounds.width - 9.0f, pos.y);
		}
	}
}