#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

struct card {
	std::string name;
	int number ;
};


struct deck {
	std::vector<std::string> cards;
	std::string card_drawn ;
	std::mt19937 gen{std::random_device{}()};

	deck(const std::vector<card> &cards_in_decklist){
		
		int space_needed = 0 ;
		for ( auto &card:cards_in_decklist ){
			space_needed += card.number ;
		}

		cards.reserve(space_needed);

		for( auto &card:cards_in_decklist ){
			for(int j = 0; j < card.number; j++){
				cards.emplace_back( card.name ) ;
			}

		}
	}

	std::string card_draw(){
		int cards_in_deck = cards.size();
		if(cards_in_deck==0){
			return "It is not possible to draw any card, you ain't got one.";
		}

		
		std::uniform_int_distribution<> dist(0, cards_in_deck-1) ;
		int rand = dist(gen) ;
		card_drawn = cards[rand];
		cards.erase(cards.begin()+rand);

		return card_drawn ; 

	}
};

/*struct deck deckbuilder(std::vector<struct card> &cards){
	struct deck dck ; 
	std::vector<std::string> list ;

	for( auto card:cards ){
		for(int j = 0; j < card.number; j++){
			list.emplace_back( card.name ) ;
		}

	}
	dck.cards = list ;
	return dck;

}*/

std::vector<card> cards_from_decklist(std::string arg ){
		std::ifstream file(arg) ;
		std::vector<card> cards;
		std::string line;
		while(std::getline(file, line)){
			std::stringstream ss(line);
			std::string loop_string;
			std::string str;
			bool found = false ;
			struct card crd;
			while(ss>>loop_string){
				if(loop_string != "-" && found == false){
					crd.name = str.append(loop_string+" ");
				} else if (loop_string != "-" && found == true){
					crd.number = std::stoi(loop_string);
				}
				if(loop_string == "-"){
					found = true;
				}
			}
			if( crd.number > 0 && !(crd.name.empty())){
				cards.emplace_back(crd);
			}

		}
		return cards ;
	
}


void initial_hand(struct deck &deck){
	int crd_in_deck = deck.cards.size() ;
	int i = 0;
	int card_to_draw = 7;
	while(i<card_to_draw){
		i++;
		std::cout << deck.card_draw() << " ";
		crd_in_deck =deck.cards.size();
		std::cout << crd_in_deck << "\n";	
	}
}

int main(int argc, char** argv){
	if (argc==1) {
		std::cout << "No argument read\n";
		return 1;
	}


	std::vector<card> cards = cards_from_decklist(argv[1]) ;

	//std::cout << cards.size() << "\n";

	/* Verify if the vector is correctly filled */
	/*for( auto i:cards){
		std::cout << i.name << " " << i.number << "\n";
	}  
	*/ //Test passed. This could be integrate as a method of the struct 

	/*Now we have to think a simple method to draw cards from the deck
	 *A simple way of doing it can be using the numbers of cards in the deck and 
	 *multiplying it for a pesudorandom number in 0 and 1
	 * */

	struct deck dck(cards) ;
	initial_hand(dck) ;

	return 0;
}
