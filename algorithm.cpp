Position2D* boxAround(SimBox* sim)
{
	Position2D boxes[4];

	int x = 0;
	int y = 0;

	x = sim->robotPos.x;
	y = sim->robotPos.y - 1;
	boxes[0] = Position2D{ x, y };

	x = sim->robotPos.x + 1;
	y = sim->robotPos.y;
	boxes[1] = Position2D{ x, y };

	x = sim->robotPos.x;
	y = sim->robotPos.y + 1;
	boxes[2] = Position2D{ x, y };

	x = sim->robotPos.x - 1;
	y = sim->robotPos.y;
	boxes[3] = Position2D{ x, y };


	return boxes;
}

void step(SimBox* sim, int** allBoxes)
{
	Position2D* list = boxAround(sim);
	Position2D boxes[4] = { list[0], list[1], list[2], list[3] };


	int values[4] = { 10000, 10000, 10000, 10000 };
	for (int i = 0; i < 4; i++)
	{

		if (boxes[i].x < 0 || boxes[i].y < 0)
		{
			values[i] == 10000;

		}
		else
		{

			values[i] = allBoxes[boxes[i].x][boxes[i].y];
		}
	}



	int front = sim->readSensorFront();
	int right = sim->readSensorRight();
	int left = sim->readSensorLeft();

	switch (sim->robotDirection)
	{
	case 0:
		if (front)
			values[0] = 10000;

		if (right)
			values[1] = 10000;

		if (left)
			values[3] = 10000;
		break;
	case 1:
		if (front)
			values[1] = 10000;

		if (right)
			values[2] = 10000;

		if (left)
			values[0] = 10000;
		break;
	case 2:
		if (front)
			values[2] = 10000;

		if (right)
			values[3] = 10000;

		if (left)
			values[1] = 10000;
		break;
	case 3:
		if (front)
			values[3] = 10000;

		if (right)
			values[0] = 10000;

		if (left)
			values[2] = 10000;
		break;
	}


	int min = 10000;
	int index = 0;

	for (int i = 0; i < 4; i++)
	{
		if (min > values[i])
		{
			min = values[i];
			index = i;
			/*if (index == sim->robotDirection)
				break;*///Arbitrary
		}
	}

	int turnCount = sim->robotDirection - index;
	if (turnCount > 0)
	{
		while (true)
		{
			if (index == sim->robotDirection)
				break;
			else
				sim->turnLeft();
		}
	}
	else
	{
		while (true)
		{
			if (index == sim->robotDirection)
				break;
			else
				sim->turnRight();
		}
	}





	/*if (front && right && left)
	{
		std::cout << "Dead-end";
		allBoxes[sim->robotPos.x][sim->robotPos.y]++;
	}*/

	sim->moveForward();
	allBoxes[sim->robotPos.x][sim->robotPos.y]++;

}
