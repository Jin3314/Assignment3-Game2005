#include "BulletPool.h"
#include <iostream>
#include <vector>

using namespace std;

BulletPool::BulletPool(int size)
{
	for (int i = 0; i < size; i++) {
		Bullet* bullet = new Bullet();
		inactive.push_back(bullet);
		all.push_back(bullet);
	}
	cout << "Bullet Pool created with size." << size << endl;

}

BulletPool::~BulletPool()
= default;

Bullet* BulletPool::Spawn()
{
	Bullet* bullet = NULL;
	if (inactive.size() > 0)
	{
		bullet = inactive.back();
		bullet->Reset();
		bullet->active = true;
		inactive.pop_back();
		active.push_back(bullet);
		cout << "Spawned" << endl;
		cout << "Active count " << to_string(active.size()) << endl;
	}
	else
	{
		cout << "ERROR: Bullet could not be spawned. Max bullets reached." << endl;
	}

	return bullet;
}

void BulletPool::Despawn(Bullet * bullet)
{
	bullet->active = false;
	inactive.push_back(bullet);

	for (std::vector<Bullet*>::iterator myiter = active.begin(); myiter != active.end(); myiter++)
	{
		if (*myiter == bullet)
		{
			active.erase(myiter);
			cout << "Despawned" << endl;
			cout << "Active count " << to_string(active.size()) << endl;
			return;

		}
	}
	
}
