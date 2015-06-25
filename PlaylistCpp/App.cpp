// App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "list"
#include "stdlib.h"
#include "time.h"
#include "string"

using namespace std;

class PlayList
{
public:
	static PlayList* Create(int n);
	void Insert(int ordinal, int trackId);
	void Delete(int ordinal);
	void Play(int ordinal);
	void Shuffle();
	void Print();
	~PlayList();

private:
	PlayList(int trackCount);
	list<int> trackIdentifiers;
	int currentlyPlayedTrackIdentifier;
};

int FetchOpCode(string operationString) {

	if (operationString == "Create") {
		return 1;
	}
	else if (operationString == "Insert") {
		return 2;
	}
	else if (operationString == "Delete") {
		return 3;
	}
	else if (operationString == "Play") {
		return 4;
	}
	else if (operationString == "Shuffle") {
		return 5;
	}
	else if (operationString == "Exit") {
		return 6;
	}
	else {
		return -1;
	}
}

int main()
{
	PlayList *playList = nullptr;
	cout << "Starting program !!";
	while (true)
	{
		cout << "\nEnter an operation 'Create', 'Insert', 'Delete', 'Play', 'Shuffle', 'Exit'" << "\n";
		string operation;
		cin >> operation;
		

		try
		{
			switch (FetchOpCode(operation))
			{
			case 1:
				int size;
				cout << "Enter the size : ";
				cin >> size;
				playList = (PlayList::Create(size));
				playList->Print();
				break;
			case 2:
				int ordinal, value;
				cout << "Enter ordinal : ";
				cin >> ordinal;
				cout << "Enter trackId : ";
				cin >> value;
				if (playList == nullptr) {
					throw "PlayList is not created yet";
				}
				playList->Insert(ordinal, value);
				playList->Print();
				break;
			case 3:
				cout << "Enter ordinal : ";
				cin >> ordinal;
				if (playList == nullptr) {
					throw "PlayList is not created yet";
				}
				playList->Delete(ordinal);
				playList->Print();
				break;
			case 4:
				cout << "Enter ordinal : ";
				cin >> ordinal;
				if (playList == nullptr) {
					throw "PlayList is not created yet";
				}
				playList->Play(ordinal);
				playList->Print();
				break;
			case 5:
				if (playList == nullptr) {
					throw "PlayList is not created yet";
				}
				playList->Shuffle();
				playList->Print();
				break;
			case 6:
				return 0;
			default:
				throw "Invalid operation";
				break;
			}
		}
		catch (const std::exception& ex)
		{
			cout << &ex;
		}
		
	}
}

PlayList::PlayList(int trackCount)
{
	for (int index = 1; index <= trackCount; index++)
	{
		trackIdentifiers.push_back(index);
	}

	currentlyPlayedTrackIdentifier = -1;
}

PlayList::~PlayList()
{
	trackIdentifiers.~list();
}

PlayList* PlayList::Create(int trackCount)
{
	if (trackCount < 0)
	{
		throw "Invalid size of playlist";
	}

	return new PlayList(trackCount);
}

void PlayList::Insert(int ordinal, int trackId)
{
	if (ordinal < 1 || ordinal > trackIdentifiers.size() + 1)
	{
		throw "Inavlid ordinal given";
	}

	auto iterator = trackIdentifiers.begin();
	for (int index = 1; index < ordinal; index++) {
		// move iterator to the position where we want to insert.
		iterator++;
	}

	trackIdentifiers.insert(iterator, trackId);

	if (ordinal < currentlyPlayedTrackIdentifier + 1) {
		currentlyPlayedTrackIdentifier++;
	}
}

void PlayList::Delete(int ordinal)
{
	if (ordinal < 1 || ordinal > trackIdentifiers.size()) {
		throw "Inavlid ordinal given";
	}

	if (ordinal == currentlyPlayedTrackIdentifier + 1) {
		currentlyPlayedTrackIdentifier = -1;
	}

	auto iterator = trackIdentifiers.begin();
	advance (iterator, ordinal - 1);
	trackIdentifiers.erase(iterator);
}

void PlayList::Play(int ordinal)
{
	if (ordinal < 1 || ordinal > trackIdentifiers.size()) {
		throw "Inavlid ordinal given";
	}

	currentlyPlayedTrackIdentifier = ordinal - 1;
}

void PlayList::Shuffle()
{
	srand(time(NULL));
	auto iterator = trackIdentifiers.begin();
	int start = 1;

	while (iterator != trackIdentifiers.end() && start < trackIdentifiers.size()-1 ) {
		if (start - 1 == currentlyPlayedTrackIdentifier) {
			if (start == 1) {
				iterator++;
				start++;
			}

			continue;
		}

		auto random = (rand() % (trackIdentifiers.size() - start)) + 1;

		if (random + start - 1 == currentlyPlayedTrackIdentifier) {
			continue;
		}
		auto iterator2 = iterator;
		advance(iterator2, random);
		iter_swap(iterator, iterator2);
		iterator++;
		start++;
	}
}

void PlayList::Print()
{
	auto iterator = trackIdentifiers.begin();
	for (int index = 0; index < trackIdentifiers.size(); index++, iterator++) {
		cout << " " << *iterator;
		if (index == currentlyPlayedTrackIdentifier) {
			cout << "*";
		}
	}
}


