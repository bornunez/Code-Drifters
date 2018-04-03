#include "SkillTree.h"

SkillTree::SkillTree(SkillTree* parent, string source, SDL_Renderer* rend, string TextSource) {
	//initial values for destRect
	skill.destRect.w = skill.destRect.x = skill.destRect.h = 50;
	skill.destRect.y = 0;

	skill.text = new Texture();
	if (skill.text->loadText(TextSource, 1, 1, rend));

	parent_ = parent;
	rending = rend;

	ifstream archivo;
	archivo.open(source);

	int numHijos; //needed for recursion call
	archivo >> numHijos;
	//id lecture
	int i =9; //first number after "..\\Arbol\\"
	//we need to read only the number, not the "..\\Arbol\\" part
	char aux;
	string aux2;
	aux = source[i];
	while (aux != '.') {
		aux2.push_back(aux);
		i++;
		aux = source[i];
	}
	skill.id = stoi(aux2); //string to int
	archivo >> skill.bought >> skill.needed_point;
	//description lecture
	string aux3 = "";
	while (!archivo.eof()) { //End Of File
		archivo >> aux3;
		//if (aux != "") { //last
		if(!archivo.fail()){
			skill.description += aux3;
			//description_ += aux;
			skill.description.push_back(' ');//space between words
		}
	}
	archivo.close();
	
	for (int i = 1; i <= numHijos; i++) {
		//the names of the files of the sons are their ids
		AddChild(new SkillTree(this,"..\\Arbol\\"+ to_string(skill.id)+to_string(i)+".txt", rending,
			"..\\Arbol\\Textures\\" + to_string(skill.id) + to_string(i) + ".png"));
	}

	skill.HLineToFather = new Texture();
	skill.VLineToFather = new Texture();
	if (!skill.bought) {
		if (skill.HLineToFather->loadText("..\\Arbol\\Textures\\Line.png", 1, 1, rend));
		if (skill.VLineToFather->loadText("..\\Arbol\\Textures\\Line.png", 1, 1, rend));
	}
	else {
		int TreeNumber = to_string(skill.id).front() - '0';
		switch (TreeNumber)
		{
		case 1:
			if (skill.HLineToFather->loadText("..\\Arbol\\Textures\\RedLine.png", 1, 1, rending));
			if (skill.VLineToFather->loadText("..\\Arbol\\Textures\\RedLine.png", 1, 1, rending));
			break;
		case 2:
			if (skill.HLineToFather->loadText("..\\Arbol\\Textures\\BlueLine.png", 1, 1, rending));
			if (skill.VLineToFather->loadText("..\\Arbol\\Textures\\BlueLine.png", 1, 1, rending));
			break;
		case 3:
			if (skill.HLineToFather->loadText("..\\Arbol\\Textures\\GreenLine.png", 1, 1, rending));
			if (skill.VLineToFather->loadText("..\\Arbol\\Textures\\GreenLine.png", 1, 1, rending));
		default:
			break;
		}
	}
	
}

SkillTree* SkillTree::FindSon(int n) {
	//id to recognize them
	if (n != skill.id) {
		//if different, we need to go deeper
		string aux = to_string(skill.id);
		aux += to_string(n)[aux.length()];
		//check if the son exists
		if(sons_[stoi(aux)%10 -1]!= nullptr)
			return sons_[stoi(aux)%10 -1]->FindSon(n);
		else return nullptr;
	}
	else return this;
}

void SkillTree::HandleEvents(SDL_Event e) {
	for (int i = 0; i < sons_.size(); i++) {
		//sons_[i]->boton->HandleEvents(e);
		sons_[i]->HandleEvents(e);
	}
}

void SkillTree::render(SDL_Rect destination, int size, int totalWidth ) {
	if (parent_ == nullptr) {
		skill.destRect.x = destination.x + destination.w / 5;
		skill.destRect.y = destination.y + destination.h / 10;
		skill.destRect.w = destination.w - ((skill.destRect.x - destination.x) * 2);
		skill.destRect.h = skill.destRect.w / 2;
	}
	else {
		skill.destRect.w = skill.destRect.h = size;
		skill.destRect.x = destination.x - skill.destRect.w / 2 + totalWidth / 2 + totalWidth/30;
		skill.destRect.y = parent_->skill.destRect.y + (parent_->skill.destRect.h) + (skill.destRect.h * (destination.h >= 450 ? 0.7 : 2));
	}

	DrawLine();
	if (parent_ != nullptr && parent_->parent_ == nullptr)
		parent_->skill.text->Render(parent_->skill.destRect, rending);
	skill.text->Render(skill.destRect, rending);

	if (sons_.size() > 0) {
		
		if (sons_.size() > 1)
			destination.x -= (destination.w / (sons_.size() * 2));
		//destination.x += destination.w / sons_.size();
		destination.w = destination.w / sons_.size();
		for (int i = 0; i < sons_.size(); i++)
		{
			sons_[i]->render(destination, size, totalWidth);
			destination.x += (destination.w);
			if(parent_ == nullptr)
				destination.x -=(size/2);
		}
	}
}

void SkillTree::Buy() {
	cout << 1;
}

string SkillTree::FindParentID() {
	if (parent_ != nullptr)
		return to_string(parent_->skill.id);
	else return "";
}

int SkillTree::TreeHeight() {
	//minimun height, only a root
	int height = 1;
	//if (parent_ != nullptr)
		//return parent_->TreeHeight();
	//else {
		if (sons_.size() > 0) {
			//the height of the first son
			int aux = sons_[0]->TreeHeight();
			for (int i = 1; i < sons_.size(); i++) {
				int aux2 = sons_[i]->TreeHeight();
				//check which son has the highest height
				if (aux < aux2)
					aux = aux2;
			}
			//minimum + height of the son
			height += aux;
		}
	//}
	return height;
}

void SkillTree::DrawLine() {
	if (parent_ != nullptr) {
		SDL_Rect auxRect;
		//horizontal line first
		auxRect.y = parent_->skill.destRect.y + parent_->skill.destRect.h / 2;
		/*if (parent_->parent_ == nullptr)
			auxRect.y += parent_->skill.destRect.h / 2;*/
		
		if (skill.destRect.x < parent_->skill.destRect.x)
			auxRect.x = skill.destRect.x + (skill.destRect.w / 2);
		else auxRect.x = parent_->skill.destRect.x + (parent_->skill.destRect.w);

		auxRect.h = skill.destRect.h/4;
		if(parent_->parent_ != nullptr)
			auxRect.w = abs(skill.destRect.x - parent_->skill.destRect.x) - parent_->skill.destRect.w / 2;
		else auxRect.w = 0;

		skill.HLineToFather->Render(auxRect, rending);
		//now line first
		if (auxRect.w <= 0) {
			auxRect.h = skill.destRect.y - parent_->skill.destRect.y - parent_->skill.destRect.h;
			/*if (parent_->parent_ == nullptr)
				auxRect.h = auxRect.h / 2;*/
			auxRect.y += parent_->skill.destRect.h / 2 +1;
		}
		else auxRect.h = skill.destRect.y - parent_->skill.destRect.y;
		auxRect.w = skill.destRect.w/4;

		auxRect.x = skill.destRect.x + (skill.destRect.w/2) - auxRect.w/2;

		skill.VLineToFather->Render(auxRect, rending);
	}
}

int SkillTree::getRootID() {
	if (parent_ == nullptr)
		return skill.id;
	else return parent_->getRootID();
}