#pragma once
#include "BasicComponent.h"
#include "imgui_plot.h"

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform;
	int id{ 1 };
};

class GameObject3DAlt
{
public:
	std::unique_ptr<Transform> transform;
	int id{ 1 };
};

class GraphComponent : public daeEngine::BasicComponent
{
public:
	explicit GraphComponent(dae::GameObject* owner);

	void RenderImgui() override;

	void CalculateGraphValuesInt(int samples);
	void CalculateGraphValuesGameObject3D(int samples);
	void CalculateGraphValuesGameObject3DAlt(int samples);

private:
	std::vector<float> m_GraphValuesInt;
	std::vector<float> m_GraphValuesGameObject3D;
	std::vector<float> m_GraphValuesGameObject3DAlt;

	int m_AmountOfSamples;

	float m_XValues[11];

	bool m_IsIntCalculated;
	bool m_IsGameObject3DCalculated;
	bool m_IsGameObject3DAltCalculated;

	ImGui::PlotConfig m_IntPlotConfig{};
	ImGui::PlotConfig m_GameObject3DPlotConfig{};
	ImGui::PlotConfig m_GameObject3DAltPlotConfig{};
};

