#include "GraphComponent.h"

#include <SDL_stdinc.h>

#include "imgui.h"
#include "imgui_plot.h"

#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include <deque>
#include <algorithm>

GraphComponent::GraphComponent(dae::GameObject* owner)
	: BasicComponent(owner),
	m_AmountOfSamples( 10 ),
	m_IsIntCalculated( false ),
	m_IsGameObject3DCalculated( false ),
	m_IsGameObject3DAltCalculated( false )
{
	for (int index{}; index < 11; ++index)
	{
		m_XValues[index] = powf(2.f, static_cast<float>(index));
	}

	m_IntPlotConfig.values.xs = m_XValues;
	m_GameObject3DPlotConfig.values.xs = m_XValues;
	m_GameObject3DAltPlotConfig.values.xs = m_XValues;
}

void GraphComponent::RenderImgui()
{
	ImGui::Begin("Exercise 2");

	//Fillable field for typing a number
	ImGui::InputInt("# Samples", &m_AmountOfSamples);

	//Button to call CalculateGraphValuesInt function
	if (ImGui::Button("Trash the cache with int"))
	{
		CalculateGraphValuesInt(m_AmountOfSamples);
	}

	//Render the graph if true
	if (m_IsIntCalculated)
	{
		ImGui::Plot("plot", m_IntPlotConfig);
	}

	//Button to call CalculateGraphValuesGameObject3D function
	if (ImGui::Button("Trash the cache with GameObject3D")) 
	{
		CalculateGraphValuesGameObject3D(m_AmountOfSamples);
	}

	//Render the graph if true
	if (m_IsGameObject3DCalculated)
	{
		ImGui::Plot("plot", m_GameObject3DPlotConfig);
	}

	//Button to call CalculateGraphValuesGameObject3DAlt function
	if (ImGui::Button("Trash the cache with GameObject3DAlt")) 
	{
		CalculateGraphValuesGameObject3DAlt(m_AmountOfSamples);
	}

	//Render the graph if true
	if (m_IsGameObject3DAltCalculated)
	{
		ImGui::Plot("plot", m_GameObject3DAltPlotConfig);
	}
	ImGui::End();
}

void GraphComponent::CalculateGraphValuesInt(int samples)
{
	m_GraphValuesInt.clear();

	//Vector of int
	std::cout << "Vector of int" << std::endl;
	std::vector<int> arr;
	arr.resize(100'000'000);
	std::fill(arr.begin(), arr.end(), 1);

	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::deque<std::chrono::milliseconds> tempValues;
		for(int sampleIndex{}; sampleIndex < samples; ++sampleIndex)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (size_t i{}; i < arr.size(); i += stepsize)
			{
				arr[i] *= 2;
			}
			auto time = std::chrono::high_resolution_clock::now();
			const auto passedTime = std::chrono::duration_cast<std::chrono::milliseconds>(time - start).count();
			tempValues.emplace_back(passedTime);
		}
		std::ranges::sort(tempValues.begin(), tempValues.end());
		tempValues.pop_back();
		tempValues.pop_front();
		std::chrono::milliseconds average{};
		for(size_t vectorIndex{}; vectorIndex < tempValues.size() - 1; ++vectorIndex)
		{
			average += tempValues[vectorIndex];
		}
		average /= static_cast<int>(tempValues.size());
		m_GraphValuesInt.emplace_back(static_cast<float>(average.count()));
	}

	const auto maxElementIterator = std::max_element(m_GraphValuesInt.begin(), m_GraphValuesInt.end());

	float largestElement{ 0.f };
	
	//When the iterator is valid get the largest element
	if (maxElementIterator != m_GraphValuesInt.end()) 
	{
		largestElement = *maxElementIterator;
	}

	m_IntPlotConfig.values.ys = m_GraphValuesInt.data();
	m_IntPlotConfig.values.count = static_cast<int>(m_GraphValuesInt.size());
	m_IntPlotConfig.scale.min = 0.f;
	m_IntPlotConfig.scale.max = largestElement;
	m_IntPlotConfig.tooltip.show = true;
	m_IntPlotConfig.tooltip.format = "x=%.2f, y=%.2f";
	m_IntPlotConfig.grid_x.show = true;
	m_IntPlotConfig.grid_y.show = true;
	m_IntPlotConfig.frame_size = ImVec2(400, 400);
	m_IntPlotConfig.line_thickness = 2.f;

	m_IsIntCalculated = true;
}

void GraphComponent::CalculateGraphValuesGameObject3D(int samples)
{
	m_GraphValuesGameObject3D.clear();

	//Vector of GameObject3D
	std::cout << "Vector of objects" << std::endl;
	std::vector<GameObject3D> arrObject;
	arrObject.resize(100'000'000);

	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::deque<std::chrono::milliseconds> tempValues;
		for (int sampleIndex{}; sampleIndex < samples; ++sampleIndex)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (size_t i{}; i < arrObject.size(); i += stepsize)
			{
				arrObject[i].id *= 2;
			}
			auto time = std::chrono::high_resolution_clock::now();
			const auto passedTime = std::chrono::duration_cast<std::chrono::milliseconds>(time - start).count();
			tempValues.emplace_back(passedTime);
		}
		std::ranges::sort(tempValues.begin(), tempValues.end());
		tempValues.pop_back();
		tempValues.pop_front();
		std::chrono::milliseconds average{};
		for (size_t vectorIndex{}; vectorIndex < tempValues.size() - 1; ++vectorIndex)
		{
			average += tempValues[vectorIndex];
		}
		average /= static_cast<int>(tempValues.size());
		m_GraphValuesGameObject3D.emplace_back(static_cast<float>(average.count()));
	}
	const auto maxElementIterator = std::max_element(m_GraphValuesGameObject3D.begin(), m_GraphValuesGameObject3D.end());

	float largestElement{ 0.f };

	//When the iterator is valid get the largest element
	if (maxElementIterator != m_GraphValuesGameObject3D.end())
	{
		largestElement = *maxElementIterator;
	}

	m_GameObject3DPlotConfig.values.ys = m_GraphValuesGameObject3D.data();
	m_GameObject3DPlotConfig.values.count = static_cast<int>(m_GraphValuesGameObject3D.size());
	m_GameObject3DPlotConfig.scale.min = 0.f;
	m_GameObject3DPlotConfig.scale.max = largestElement;
	m_GameObject3DPlotConfig.tooltip.show = true;
	m_GameObject3DPlotConfig.tooltip.format = "x=%.2f, y=%.2f";
	m_GameObject3DPlotConfig.grid_x.show = true;
	m_GameObject3DPlotConfig.grid_y.show = true;
	m_GameObject3DPlotConfig.frame_size = ImVec2(400, 400);
	m_GameObject3DPlotConfig.line_thickness = 2.f;

	m_IsGameObject3DCalculated = true;
}

void GraphComponent::CalculateGraphValuesGameObject3DAlt(int samples)
{
	m_GraphValuesGameObject3DAlt.clear();

	//Vector of GameObject3DAlt
	std::cout << "Vector of objects" << std::endl;
	std::vector<GameObject3DAlt> arrObjectAlt;
	arrObjectAlt.resize(100'000'000);

	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::deque<std::chrono::milliseconds> tempValues;
		for (int sampleIndex{}; sampleIndex < samples; ++sampleIndex)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (size_t i{}; i < arrObjectAlt.size(); i += stepsize)
			{
				arrObjectAlt[i].id *= 2;
			}
			auto time = std::chrono::high_resolution_clock::now();
			const auto passedTime = std::chrono::duration_cast<std::chrono::milliseconds>(time - start).count();
			tempValues.emplace_back(passedTime);
		}
		std::ranges::sort(tempValues.begin(), tempValues.end());
		tempValues.pop_back();
		tempValues.pop_front();
		std::chrono::milliseconds average{};
		for (size_t vectorIndex{}; vectorIndex < tempValues.size() - 1; ++vectorIndex)
		{
			average += tempValues[vectorIndex];
		}
		average /= static_cast<int>(tempValues.size());
		m_GraphValuesGameObject3DAlt.emplace_back(static_cast<float>(average.count()));
	}
	const auto maxElementIterator = std::max_element(m_GraphValuesGameObject3DAlt.begin(), m_GraphValuesGameObject3DAlt.end());

	float largestElement{ 0.f };

	//When the iterator is valid get the largest element
	if (maxElementIterator != m_GraphValuesGameObject3DAlt.end())
	{
		largestElement = *maxElementIterator;
	}

	m_GameObject3DAltPlotConfig.values.ys = m_GraphValuesGameObject3DAlt.data();
	m_GameObject3DAltPlotConfig.values.count = static_cast<int>(m_GraphValuesGameObject3DAlt.size());
	m_GameObject3DAltPlotConfig.scale.min = 0.f;
	m_GameObject3DAltPlotConfig.scale.max = largestElement;
	m_GameObject3DAltPlotConfig.tooltip.show = true;
	m_GameObject3DAltPlotConfig.tooltip.format = "x=%.2f, y=%.2f";
	m_GameObject3DAltPlotConfig.grid_x.show = true;
	m_GameObject3DAltPlotConfig.grid_y.show = true;
	m_GameObject3DAltPlotConfig.frame_size = ImVec2(400, 400);
	m_GameObject3DAltPlotConfig.line_thickness = 2.f;

	m_IsGameObject3DAltCalculated = true;
}
