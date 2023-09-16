#include <iostream>
#include <random>
#include <array>
#include <algorithm>
#include <ctime>    
#include <chrono>

using Piece = std::array<u_int8_t, 6>;
using Pieces  = std::array<Piece, 7>;

void rotate(Piece &piece, int n)
{
	std::rotate(piece.begin(), piece.begin() + n, piece.end());
}

class RandomSolver
{
	public:
	Pieces pieces;

	explicit RandomSolver(Pieces pieces) : pieces(pieces) {}

	bool check_state()
	{
		return (pieces[0][0] == pieces[1][3])
		&& (pieces[0][1] == pieces[2][4])
		&& (pieces[0][2] == pieces[3][5])
		&& (pieces[0][3] == pieces[4][0])
		&& (pieces[0][4] == pieces[5][1])
		&& (pieces[0][5] == pieces[6][2])
		&& (pieces[1][2] == pieces[2][5])
		&& (pieces[2][3] == pieces[3][0])
		&& (pieces[3][4] == pieces[4][1])
		&& (pieces[4][5] == pieces[5][2])
		&& (pieces[5][0] == pieces[6][3])
		&& (pieces[6][1] == pieces[1][4]);
	}

	void shuffle()
	{
		shuffle_pieces();
		shuffle_positions();
	}

	void shuffle_positions()
	{
		std::shuffle(std::begin(pieces), std::end(pieces), rng);
	}

	void turn_piece_randomly(Piece &piece)
	{
		rotate(piece, uni(rng));
	}

	void shuffle_pieces()
	{
		for (auto &piece : pieces){
			turn_piece_randomly(piece);
		}
	}

	bool solve()
	{
		int counter = 0;
		auto solved = check_state();
		while (not check_state())
		{
			shuffle();
			counter++;
			if ((counter % 10000000) == 0)
			{
				std::cout << counter << std::endl;
			}
			break;
		}
		return true;
	} 

	private:
		std::random_device rd{}; 
		std::default_random_engine rng{ rd() };
		std::uniform_int_distribution<int> uni{0,5}; // Guaranteed unbiased
};

int main(int argc, const char** argv) {

	Piece p0 {1, 6, 2, 4, 5, 3};
	Piece p1 {1, 4, 3, 6, 5, 2};
	Piece p2 {1, 2, 3, 4, 5, 6};
	Piece p3 {1, 4, 6, 2, 3, 5};
	Piece p4 {1, 6, 5, 4, 3, 2};
	Piece p5 {1, 6, 4, 2, 5, 3};
	Piece p6 {1, 6, 5, 3, 2, 4};

	std::array<Piece,7> pieces = {p0, p1, p2, p3, p4, p5, p6};

	auto solver = RandomSolver(pieces);
	auto solved = solver.solve();

	// print solution
	for (auto piece : pieces)
	{
		for (auto num : piece)
			{std::cout<<+num<<" ";}
		std::cout << std::endl;
	}
	return 0;
}
