#include "monster.hpp"

//constructor for monster
//creates the png for the monster and sets the size of the monster
Monster::Monster(sf::RenderWindow& window) :Player("../data/images/Character_Sheet.png", .8f) //image location on file, speed
{
	attackRadius.setScale(5, 5);
	attackRadius.setSize(sf::Vector2f(20, 20));
	attackRadius.setFillColor(sf::Color::Red);
	MonsterRadius.setScale(5, 5);
	MonsterRadius.setSize(sf::Vector2f(160, 126));
	MonsterRadius.setFillColor(sf::Color(0, 0, 0, 0));

	//debugging radius color
	//MonsterRadius.setFillColor(Color(0, 255, 255, 100));
	LOS.setFillColor(sf::Color(0, 0, 0, 0));

	size = sf::Vector2f(5.f, 5.f);
	sprite.setTextureRect(sf::IntRect(11 * 16, 7 * 16, 16, 16));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height);
	setPosition(2000, 6000);

	//Debugging - Sets sprite to center of window at start
	//sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

//handles movement of the monster based on the player position
void Monster::handlePlayerMovement(float dt, Walls& walls, Survivor& survivor, sf::RenderWindow& window) 
{
  //get position to attack the player if in radius
	attackRadius.setPosition(sprite.getPosition());
	attackRadius.setOrigin(attackRadius.getLocalBounds().width / 2, attackRadius.getLocalBounds().height / 2);
	MonsterRadius.setPosition(sprite.getPosition());
	MonsterRadius.setOrigin(MonsterRadius.getLocalBounds().width / 2, MonsterRadius.getLocalBounds().height / 2);
	window.draw(MonsterRadius);
  sf::RectangleShape* worldBarriers = walls.getBarriers();


	//Checks if there is a wall blocking LOS (Line of Sight)
	for (int i = 0; i < walls.getBarriersCount(); i++)
	{
		if (LOS.getGlobalBounds().intersects(worldBarriers[i].getGlobalBounds())) 
    {
			lostLOS = true;
			break;
		}
		else 
    {
			lostLOS = false;
		}
	}

	//idle movement when player is not in radius of monster
	if (!MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds()) || lostLOS) 
  {
		// Calculate new position based on current direction and speed
		speed = 0.05f;
		if (!CollidesWithWalls(walls, dt)) 
    {
			sprite.move(moveDirection * speed * dt);
			MonsterRadius.move(moveDirection * speed * dt);
		}
		if (CollidesWithWalls(walls, dt)) 
    {
			sprite.move(moveDirection.x / -1 * dt, moveDirection.y / -1 * dt);
			MonsterRadius.move(moveDirection.x / -1 * dt, moveDirection.y / -1 * dt);
			// Change direction to avoid getting stuck in a wall
			moveDirection = changeDirection();
		}
	}

	//If the monster has LOS
	if (!lostLOS) 
  {
		//MoveRight
		if (getPosition().x < survivor.getPosition().x && MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) 
    {
			move(.1f * dt, 0.f);
			MonsterRadius.move(.1f * dt, 0.f);
			for (int i = 0; i < walls.getBarriersCount(); i++)
			{
				if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) 
        {
					move(-.1f * dt, 0.f);
					MonsterRadius.move(-.1f * dt, 0.f);
				}
			}


		}
		//MoveLeft
		if (getPosition().x > survivor.getPosition().x && MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) 
    {
			move(-.1f * dt, 0.f);
			MonsterRadius.move(-.1f * dt, 0.f);
			for (int i = 0; i < walls.getBarriersCount(); i++)
			{
				if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) 
        {
					move(.1f * dt, 0.f);
					MonsterRadius.move(.1f * dt, 0.f);
				}
			}

		}
		//MoveUp
		if (getPosition().y > survivor.getPosition().y && MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) 
    {
			move(0.f * dt, -.1f * dt);
			MonsterRadius.move(0.f * dt, -.1f);
			for (int i = 0; i < walls.getBarriersCount(); i++)
			{
				if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) 
        {
					move(0.f * dt, .1f * dt);
				}
			}

		}
		//MoveDown
		if (getPosition().y < survivor.getPosition().y && MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) 
    {
			move(0.f, .1f * dt);
			MonsterRadius.move(0.f * dt, .1f);
			for (int i = 0; i < walls.getBarriersCount(); i++)
			{
				if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) 
        {
					move(0.f, -.1f * dt);
					MonsterRadius.move(0.f * dt, -.1f);
				}
			}
		}
	}
}

sf::Vector2f Monster::getSize()
{
	return sf::Vector2f();
}

void Monster::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	MonsterRadius.setPosition(x, y);
}

void Monster::directionUpdate(sf::RenderWindow& window, Survivor& survivor)
{
	directionLook(window, survivor.getPosition().x, survivor.getPosition().y);
}


//tells the monster which direction to look
void Monster::directionLook(sf::RenderWindow& window, float x2, float y2) 
{

	float x1 = sprite.getPosition().x;
	float y1 = sprite.getPosition().y;

	//pythag for finding angle of rotation
	float adj = x2 - x1;
	float op = y2 - y1;

	//calc angle for direction
	float angleRads = atan2(op, adj);
	float angleDeg = (angleRads * 180 / 3.141592654);

	//Sets LOS values
	LOS.setSize(sf::Vector2f(sqrt(pow(adj, 2) + pow(op, 2)), 1));
	LOS.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	LOS.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	LOS.setRotation(angleDeg);

	//Debugging for LOS
	//window.draw(LOS);

	//Adjust sprite based on direction looked
	if (angleDeg < 45 && angleDeg > -45) {
		sprite.setScale(5.f, 5.f);
		sprite.setTextureRect(sf::IntRect(13 * 16, 7 * 16, 16, 16));
	}
	if (angleDeg < -45 && angleDeg > -135) {
		sprite.setTextureRect(sf::IntRect(12 * 16, 7 * 16, 16, 16));
	}
	if (angleDeg < -135 || angleDeg > 135) {
		sprite.setScale(-5.f, 5.f);
		sprite.setTextureRect(sf::IntRect(13 * 16, 7 * 16, 16, 16));
	}
	if (angleDeg < 135 && angleDeg > 45) {
		sprite.setTextureRect(sf::IntRect(11 * 16, 7 * 16, 16, 16));
	}
}

sf::RectangleShape Monster::getMonsterRadius() 
{
	return MonsterRadius;
}

sf::RectangleShape Monster::getAttackRadius()
{
	return attackRadius;
}

//changes the direction of the monster randomly
sf::Vector2f Monster::changeDirection() 
{
	// Generate a random angle between 0 and 2*pi
	float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * 3.14159265359f;

	// Calculate x and y components of the direction from the angle
	float newX = std::cos(angle);
	float newY = std::sin(angle);

	return sf::Vector2f(newX, newY);
}


//attacks player and subtracts health
void Monster::attackPlayer(Survivor& survivor) 
{
	// Check if the attack cooldown is over
	if (attackClock.getElapsedTime().asSeconds() >= attackCooldown) 
  {
		survivor.updateHealth(20.0f); // Deal 20 damage
		resetAttackCooldown();
	}
}

void Monster::resetAttackCooldown() 
{
	attackClock.restart();
}
