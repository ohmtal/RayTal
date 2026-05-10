#include "RayFlux/Main.h"
#include "RayFlux/Gui.h"

// from rayspice
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include <string>
#include <math.h>
//------------------------------------------------------------------------------
using namespace RayFlux::Tools;

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            100 //330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

//------------------------------------------------------------------------------


int main(void)
{
    RayFlux::Main app;
    app.getSettings()->WindowMaximized = true;
    app.getSettings()->IconFilename = "texture:/raylib_32x32.png";
    // app.settings.FullScreen = true;

    if (!app.Init()) {
        TraceLog(LOG_ERROR, "%s", "Failed to Initialize!");
        return 1;
    }

    // Music
    app.playMusic("fullhouse2026.fms.mp3", 0.75f);

    // Texture
    Texture2D *logoTex = app.getResourceManager()->getTexture("raylib_32x32.png");

    //-------
    // add basic lighting demo .....
    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 4.0f, 6.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Load basic lighting shader
    Shader shader = LoadShader(TextFormat("assets/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                               TextFormat("assets/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    // Get some required shader locations
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    // NOTE: "matModel" location name is automatically assigned on shader loading,
    // no need to get the location again if using that uniform name
    //shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (F32[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);

    // Create lights
    Light lights[MAX_LIGHTS] = { {0} };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, -2 }, Vector3Zero(), YELLOW, shader);
    lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, 2 }, Vector3Zero(), RED, shader);
    lights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, 2 }, Vector3Zero(), GREEN, shader);
    lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, -2 }, Vector3Zero(), BLUE, shader);

    lights[0].color=ORANGE;

    // ------- eyes

    Vector2 scleraLeftPosition = { GetScreenWidth() - 200.0f, GetScreenHeight() - 100.f };
    Vector2 scleraRightPosition = { GetScreenWidth() - 60.0f, GetScreenHeight() - 100.f };
    F32 scleraRadius = 60;

    Vector2 irisLeftPosition = scleraLeftPosition;
    Vector2 irisRightPosition = scleraRightPosition;
    F32 irisRadius = 24;

    F32 angle = 0.0f;
    F32 dx = 0.0f, dy = 0.0f, dxx = 0.0f, dyy = 0.0f;

    //-------
    std::string confPathText = TextFormat("Base Path: %s", getBasePath().c_str());
    std::string prefPathText = TextFormat("Config Path: %s", app.getSettings()->getPrefsPath().c_str());
    RayFlux::LazyGui lg {10, 10, 20};

    //------
    app.OnUpdate = [&](F32 dt) {

        UpdateCamera(&camera, CAMERA_ORBITAL);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        F32 cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }

        // Update light values (actually, only enable/disable them)
        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);


        // Eyes
        //----------------------------------------------------------------------------------
        if (IsWindowResized()) { // FIXME EVENT !!
            // int newWidth = GetScreenWidth();
            // int newHeight = GetScreenHeight();
            scleraLeftPosition = { GetScreenWidth() - 200.0f, GetScreenHeight() - 100.f };
            scleraRightPosition = { GetScreenWidth() - 60.0f, GetScreenHeight() - 100.f };
        }

        irisLeftPosition = GetMousePosition();
        irisRightPosition = GetMousePosition();

        // Check not inside the left eye sclera
        if (!CheckCollisionPointCircle(irisLeftPosition, scleraLeftPosition, scleraRadius - irisRadius))
        {
            dx = irisLeftPosition.x - scleraLeftPosition.x;
            dy = irisLeftPosition.y - scleraLeftPosition.y;

            angle = atan2f(dy, dx);

            dxx = (scleraRadius - irisRadius)*cosf(angle);
            dyy = (scleraRadius - irisRadius)*sinf(angle);

            irisLeftPosition.x = scleraLeftPosition.x + dxx;
            irisLeftPosition.y = scleraLeftPosition.y + dyy;
        }

        // Check not inside the right eye sclera
        if (!CheckCollisionPointCircle(irisRightPosition, scleraRightPosition, scleraRadius - irisRadius))
        {
            dx = irisRightPosition.x - scleraRightPosition.x;
            dy = irisRightPosition.y - scleraRightPosition.y;

            angle = atan2f(dy, dx);

            dxx = (scleraRadius - irisRadius)*cosf(angle);
            dyy = (scleraRadius - irisRadius)*sinf(angle);

            irisRightPosition.x = scleraRightPosition.x + dxx;
            irisRightPosition.y = scleraRightPosition.y + dyy;
        }
    };
    //------
    app.OnRender = [&]() {

        BeginMode3D(camera);
            BeginShaderMode(shader);
            DrawPlane(Vector3Zero(), (Vector2) { 10.0, 10.0 }, WHITE);
            DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);
            EndShaderMode();
            // Draw spheres to show where the lights are
            for (int i = 0; i < MAX_LIGHTS; i++)
            {
                if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
                else DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
            }
            DrawGrid(10, 1.0f);
        EndMode3D();

        // eyes
        DrawCircleV(scleraLeftPosition, scleraRadius, LIGHTGRAY);
        DrawCircleV(irisLeftPosition, irisRadius, BROWN);
        DrawCircleV(irisLeftPosition, 10, BLACK);

        DrawCircleV(scleraRightPosition, scleraRadius, LIGHTGRAY);
        DrawCircleV(irisRightPosition, irisRadius, DARKGREEN);
        DrawCircleV(irisRightPosition, 10, BLACK);

        lg.y = 10;

        // logo
        if (logoTex) DrawTexture(*logoTex, lg.x, lg.x, WHITE);
        lg.y += 40.f;
        lg.size = 40;
        lg.Write("RayLib Test .....", GOLD);
        lg.size = 20;
        lg.Write(TextFormat("FPS: %d", GetFPS()),  RED);
        lg.size = 10;
        lg.Write(confPathText.c_str(), ORANGE);
        lg.Write(prefPathText.c_str(), SKYBLUE);
        lg.Write(logoTex ? "Logo loaded" : "Logo failed!");
        lg.size = 20;
        lg.Write("LIGHTS:", WHITE);
        lg.CheckBox( "Red", &lights[1].enabled);
        lg.CheckBox( "Green", &lights[2].enabled);
        lg.CheckBox( "Blue", &lights[3].enabled);
        lg.CheckBox( "Yellow", &lights[0].enabled);


        if (lg.Button(100.f, "Test Sound" ) == 1) {
            app.playSound("flee.mp3");
        }
    };
    //--------
    app.OnShutDown = [&]() {
        UnloadShader(shader);
    };
    //--------
    app.Execute();

    return 0;
}
