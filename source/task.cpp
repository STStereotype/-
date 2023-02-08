#include "task.h"
#include <cmath>
#include <thread>
#include <atomic>
#define DEG_PI 57.295791

void Task::checkVisible(const std::vector<unit>& input_units,
    std::vector<int>& result)
{
	int size = input_units.size();
	result.resize(size);
	const unit* units_ptr = input_units.data();
	int* result_ptr = result.data();
	auto algorithm = [&input_units, size](const unit& hunter) -> int
	{
		int num_caught{ 0 };
		float pow_dist = hunter.distance * hunter.distance;
		float half_angle = cos((hunter.fov_deg / 2.f) / DEG_PI);
		vec2 hunter_position = { hunter.position.x, hunter.position.y };
		vec2 hunter_direction = { hunter.direction.x, hunter.direction.y };    
		for (const unit& booty : input_units)
		{
			vec2 direction = { booty.position.x - hunter_position.x,
				booty.position.y - hunter_position.y };
			float length = direction.x * direction.x +
				direction.y * direction.y;
			if (length > pow_dist)
				continue;
			float scalar = direction.x * hunter_direction.x +
				direction.y * hunter_direction.y;
			if (scalar <= 0.f)
				continue;
			float angle_cos = scalar / sqrtf(length);
			if (angle_cos > 0.999f || angle_cos > half_angle)
				++num_caught;
		}
		return num_caught;
	};

	std::atomic<int> index{ 0 };
	auto start = [&]()  -> void
	{
		while (index < size)
		{
			int local_index = index++;
			if (local_index >= size)
				break;
			*(result_ptr + local_index) =  algorithm(*(units_ptr + local_index));
		}
	};

	int num_threads = std::thread::hardware_concurrency() - 1;
	std::vector<std::thread> threads;
	threads.reserve(num_threads);
	for (int i = 0; i < num_threads; ++i)
		threads.emplace_back(start);
	start();
	for (std::thread& thrd : threads)
		thrd.join();
}