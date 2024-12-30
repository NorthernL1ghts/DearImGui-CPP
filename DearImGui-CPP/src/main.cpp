#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <vector>
#include <string>

// Global variables
GLFWwindow* g_Window = nullptr;
ImVec4 g_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

// Class to handle ImGui
class ImGuiManager
{
public:
	bool showDemoWindow = true;
	bool showAnotherWindow = false;
	float floatValue = 0.0f;
	int counter = 0;
	bool showAppMetrics = false;
	bool showAppStyleEditor = false;
	bool showAppAbout = false;
	std::vector<std::string> items = { "Apple", "Banana", "Cherry", "Date", "Elderberry", "Fig", "Grapes" };
	int itemCurrentIdx = 0;

	void RenderImGui()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (showDemoWindow)
			ImGui::ShowDemoWindow(&showDemoWindow);

		if (showAppMetrics)
			ImGui::ShowMetricsWindow(&showAppMetrics);

		if (showAppStyleEditor)
		{
			ImGui::Begin("Style Editor", &showAppStyleEditor);
			ImGui::ShowStyleEditor();
			ImGui::End();
		}

		if (showAppAbout)
		{
			ImGui::Begin("About Dear ImGui", &showAppAbout, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text("Dear ImGui, %s", IMGUI_VERSION);
			ImGui::Separator();
			ImGui::Text("By Omar Cornut and all dear imgui contributors.");
			ImGui::End();
		}

		ImGui::Begin("Hello, world!");
		ImGui::Text("This is some useful text.");
		ImGui::Checkbox("Demo Window", &showDemoWindow);
		ImGui::Checkbox("Another Window", &showAnotherWindow);
		ImGui::Checkbox("App Metrics", &showAppMetrics);
		ImGui::Checkbox("Style Editor", &showAppStyleEditor);
		ImGui::Checkbox("About", &showAppAbout);

		ImGui::SliderFloat("Float Value", &floatValue, 0.0f, 1.0f);
		ImGui::ColorEdit3("Clear Color", (float*)&g_ClearColor);

		if (ImGui::Button("Button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("Counter = %d", counter);

		const char* comboPreviewValue = items[itemCurrentIdx].c_str();
		if (ImGui::BeginCombo("Combo", comboPreviewValue))
		{
			for (int n = 0; n < items.size(); n++)
			{
				const bool isSelected = (itemCurrentIdx == n);
				if (ImGui::Selectable(items[n].c_str(), isSelected))
					itemCurrentIdx = n;
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::End();

		if (showAnotherWindow)
		{
			ImGui::Begin("Another Window", &showAnotherWindow);
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				showAnotherWindow = false;
			ImGui::End();
		}

		ImGui::Render();
		int displayW, displayH;
		glfwGetFramebufferSize(g_Window, &displayW, &displayH);
		glViewport(0, 0, displayW, displayH);
		glClearColor(g_ClearColor.x, g_ClearColor.y, g_ClearColor.z, g_ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(g_Window);
	}
};

// Error callback function
static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool InitializeWindow(const char* glslVersion)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return false;

	g_Window = glfwCreateWindow(1280, 720, "Dear ImGui Advanced Example", NULL, NULL);
	if (g_Window == NULL)
		return false;

	glfwMakeContextCurrent(g_Window);
	glfwSwapInterval(1); // Enable vsync

	glViewport(0, 0, 1280, 720);
	glClearColor(g_ClearColor.x, g_ClearColor.y, g_ClearColor.z, g_ClearColor.w);

	return true;
}

void InitializeImGui(const char* glslVersion)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(g_Window, true);
	ImGui_ImplOpenGL3_Init(glslVersion);
}

void Cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(g_Window);
	glfwTerminate();
}

int main(int, char**)
{
	const char* glslVersion = "#version 130";

	if (!InitializeWindow(glslVersion))
		return -1;

	InitializeImGui(glslVersion);

	ImGuiManager imguiManager;

	while (!glfwWindowShouldClose(g_Window))
	{
		glfwPollEvents();
		imguiManager.RenderImGui();
	}

	Cleanup();

	return 0;
}
