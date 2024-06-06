#include "monster.hpp"

/*****************************************
Function Name: Monster
Date Created: 04/22/2024
Description: Constructor for Monster class.
Input parameters:
	- window: Reference to the RenderWindow.
Returns: None
*******************************************/
Monster::Monster(RenderWindow& window) :Player("../data/images/Character_Sheet.png", .8f) //image location on file, speed
{
	attackRadius.setScale(5, 5);
	attackRadius.setSize(Vector2f(20, 20));
	attackRadius.setFillColor(Color::Red);
	MonsterRadius.setScale(5, 5);
	MonsterRadius.setSize(Vector2f(160, 126));
	MonsterRadius.setFillColor(Color(0, 0, 0, 0));

	//debugging radius color
	//MonsterRadius.setFillColor(Color(0, 255, 255, 100));
	LOS.setFillColor(Color(0, 0, 0, 0));

	size = Vector2f(5.f, 5.f);
	sprite.setTextureRect(IntRect(11 * 16, 7 * 16, 16, 16));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height);
	setPosition(2000, 6000);

	//Debugging - Sets sprite to center of window at start
	//sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

/*****************************************
Function Name: handlePlayerMovement
Date Created: 04/22/2024
Description: Handles movement of the monster based on player position.
Input parameters:
	- dt: Time elapsed since last frame.
	- walls: Reference to Walls object.
	- survivor: Reference to Survivor object.
	- window: Reference to RenderWindow.
Returns: void
*******************************************/
void Monster::handlePlayerMovement(float dt, Walls& walls, Survivor& survivor, RenderWindow& window) {
	attackRadius.setPosition(sprite.getPosition());
	attackRadius.setOrigin(attackRadius.getLocalBounds().width / 2, attackRadius.getLocalBounds().height / 2);
	MonsterRadius.setPosition(sprite.getPosition());
	MonsterRadius.setOrigin(MonsterRadius.getLocalBounds().width / 2, MonsterRadius.getLocalBounds().height / 2);
	window.draw(MonsterRadius);
	RectangleShape* worldBarriers = walls.getBarriers();


	//Checks if there is a wall blocking LOS (Line of Sight)
	for (int i = 0; i < walls.getBarriersCount(); i++)
	{
		if (LOS.getGlobalBounds().intersects(worldBarriers[i].getGlobalBounds())) {
			lostLOS = true;
			break;
		}
		else {
			lostLOS = false;
		}
	}

	//idle movement when player is not in radius of monster
	if (!MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds()) || lostLOS) {
		// Calculate new position based on current direction and speed
		speed = 0.05f;
		if (!CollidesWithWalls(walls, dt)) {
			sprite.move(moveDirection * speed * dt);
			MonsterRadius.move(moveDirection * speed * dt);
		}
		if (CollidesWithWalls(walls, dt)) {
			sprite.move(moveDirection.x / -1 * dt, moveDirection.y / -1 * dt);
			MonsterRadius.move(moveDirection.x / -1 * dt, moveDirection.y / -1 * dt);
			// Change direction to avoid getting stuck in a wall
			moveDirection = changeDirection();
		}
	}

	//If the monster has LOS
	if (!lostLOS) {
		//MoveRight
		if (getPosition().x < survivor.getPosition().x && MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) {
			move(.1f * dt, 0.f);
			MonsterRadius.move(.1f * dt, 0.f);
			for (int i = 0; i < walls.getBarriersCount(); i++)
			{
				if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) {
					move(-.1f * dt, 0.f);
					MonsterRadius.move(-.1f * dt, 0.f);
				}
			}


		}
		//MoveLeft
		if (getPosition().x > survivor.getPosition().x && MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) {
			move(-.1f * dt, 0.f);
			MonsterRadius.move(-.1f * dt, 0.f);
			for (int i = 0; i < walls.getBarriersCount(); i++)
			{
				if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) {
					move(.1f * dt, 0.f);
					MonsterRadius.move(.1f * dt, 0.f);
				}
			}

		}
		//MoveUp
		if (getPosition().y > survivor.getPosition().y && MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) {
			move(0.f * dt, -.1f * dt);
			MonsterRadius.move(0.f * dt, -.1f);
			for (int i = 0; i < walls.getBarriersCount(); i++)
			{
				if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) {
					move(0.f * dt, .1f * dt);
				}
			}

		}
		//MoveDown
		if (getPosition().y < survivor.getPosition().y && MonsterRadius.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) {
			move(0.f, .1f * dt);
			MonsterRadius.move(0.f * dt, .1f);
			for (int i = 0; i < walls.getBarriersCount(); i++)
			{
				if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) {
					move(0.f, -.1f * dt);
					MonsterRadius.move(0.f * dt, -.1f);
				}
			}
		}
	}
}

/*****************************************
Function Name: getSize
Date Created: 04/22/2024
Description: Gets the size of the Monster sprite.
Input parameters: None
Returns:
	- Vector2f representing the size of the sprite.
*******************************************/
Vector2f Monster::getSize()
{
	return Vector2f();
}

/*****************************************
Function Name: setPosition
Date Created: 04/22/2024
Description: Sets the position of the Monster sprite.
Input parameters:
	- x: X coordinate of the new position.
	- y: Y coordinate of the new position.
Returns: void
*******************************************/
void Monster::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	MonsterRadius.setPosition(x, y);
}

/*****************************************
Function Name: directionUpdate
Date Created: 04/22/2024
Description: Updates the Monster's direction based on player position.
Input parameters:
	- window: Reference to RenderWindow.
	- survivor: Reference to Survivor object.
Returns: void
*******************************************/
void Monster::directionUpdate(RenderWindow& window, Survivor& survivor)
{
	directionLook(window, survivor.getPosition().x, survivor.getPosition().y);
}


/*****************************************
Function Name: directionLook
Date Created: 04/22/2024
Description: Calculates the direction the Monster looks towards.
Input parameters:
	- window: Reference to RenderWindow.
	- x2: X coordinate of the target position.
	- y2: Y coordinate of the target position.
Returns: void
*******************************************/
void Monster::directionLook(RenderWindow& window, float x2, float y2) {

	float x1 = sprite.getPosition().x;
	float y1 = sprite.getPosition().y;

	//pythag for finding angle of rotation
	float adj = x2 - x1;
	float op = y2 - y1;

	//calc angle for direction
	float angleRads = atan2(op, adj);
	float angleDeg = (angleRads * 180 / 3.141592654);

	//Sets LOS values
	LOS.setSize(Vector2f(sqrt(pow(adj, 2) + pow(op, 2)), 1));
	LOS.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	LOS.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	LOS.setRotation(angleDeg);

	//Debugging for LOS
	//window.draw(LOS);

	//Adjust sprite based on direction looked
	if (angleDeg < 45 && angleDeg > -45) {
		sprite.setScale(5.f, 5.f);
		sprite.setTextureRect(IntRect(13 * 16, 7 * 16, 16, 16));
	}
	if (angleDeg < -45 && angleDeg > -135) {
		sprite.setTextureRect(IntRect(12 * 16, 7 * 16, 16, 16));
	}
	if (angleDeg < -135 || angleDeg > 135) {
		sprite.setScale(-5.f, 5.f);
		sprite.setTextureRect(IntRect(13 * 16, 7 * 16, 16, 16));
	}
	if (angleDeg < 135 && angleDeg > 45) {
		sprite.setTextureRect(IntRect(11 * 16, 7 * 16, 16, 16));
	}
}

/*****************************************
Function Name: getMonsterRadius
Date Created: 04/22/2024
Description: Gets the Monster's LOS radius.
Input parameters: None
Returns:
	- RectangleShape representing the Monster's LOS radius.
*******************************************/
RectangleShape Monster::getMonsterRadius() {
	return MonsterRadius;
}

RectangleShape Monster::getAttackRadius()
{
	return attackRadius;
}

/*****************************************
Function Name: changeDirection
Date Created: 04/22/2024
Description: Changes the Monster's movement direction.
Input parameters: None
Returns:
	- Vector2f representing the new movement direction.
*******************************************/
Vector2f Monster::changeDirection() {
	// Generate a random angle between 0 and 2*pi
	float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * 3.14159265359f;

	// Calculate x and y components of the direction from the angle
	float newX = std::cos(angle);
	float newY = std::sin(angle);

	return sf::Vector2f(newX, newY);
}


void Monster::attackPlayer(Survivor& survivor) {
	// Check if the attack cooldown is over
	if (attackClock.getElapsedTime().asSeconds() >= attackCooldown) {
		survivor.updateHealth(20.0f); // Deal 20 damage
		std::cout << "Damage Taken: 20" << std::endl;
		std::cout << "Current Health: " << survivor.getHealth() << std::endl;
		resetAttackCooldown();
	}
}

void Monster::resetAttackCooldown() {
	attackClock.restart();
}
