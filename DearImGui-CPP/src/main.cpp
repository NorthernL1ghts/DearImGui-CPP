#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <vector>
#include <string>

// Error callback function
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return -1;

	// Create window with graphics context
	const char* glsl_version = "#version 130";
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui Advanced Example", NULL, NULL);
	if (window == NULL)
		return -1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Setup OpenGL context
	glViewport(0, 0, 1280, 720);
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Variables for ImGui
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	float f = 0.0f;
	int counter = 0;
	bool show_app_metrics = false;
	bool show_app_style_editor = false;
	bool show_app_about = false;
	std::vector<std::string> items = { "Apple", "Banana", "Cherry", "Date", "Elderberry", "Fig", "Grapes" };
	int item_current_idx = 0;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		glfwPollEvents();

		// Start the ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Show a demo window
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// Show application metrics window
		if (show_app_metrics)
			ImGui::ShowMetricsWindow(&show_app_metrics);

		// Show application style editor window
		if (show_app_style_editor)
		{
			ImGui::Begin("Style Editor", &show_app_style_editor);
			ImGui::ShowStyleEditor();
			ImGui::End();
		}

		// Show application about window
		if (show_app_about)
		{
			ImGui::Begin("About Dear ImGui", &show_app_about, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text("Dear ImGui, %s", IMGUI_VERSION);
			ImGui::Separator();
			ImGui::Text("By Omar Cornut and all dear imgui contributors.");
			ImGui::End();
		}

		// Show a simple window
		{
			ImGui::Begin("Hello, world!");
			ImGui::Text("This is some useful text.");
			ImGui::Checkbox("Demo Window", &show_demo_window);
			ImGui::Checkbox("Another Window", &show_another_window);
			ImGui::Checkbox("App Metrics", &show_app_metrics);
			ImGui::Checkbox("Style Editor", &show_app_style_editor);
			ImGui::Checkbox("About", &show_app_about);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			// Combo box
			const char* combo_preview_value = items[item_current_idx].c_str(); // Pass in the preview value visible before opening the combo (it could be anything)
			if (ImGui::BeginCombo("combo", combo_preview_value))
			{
				for (int n = 0; n < items.size(); n++)
				{
					const bool is_selected = (item_current_idx == n);
					if (ImGui::Selectable(items[n].c_str(), is_selected))
						item_current_idx = n;
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::End();
		}

		// Show another simple window
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
