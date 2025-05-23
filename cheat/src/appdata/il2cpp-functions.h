// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Target Unity version: 2021.2.0+

// ******************************************************************************
// * IL2CPP application-specific method definition addresses and signatures
// ******************************************************************************
using namespace app;

// C# methods
DO_APP_FUNC(0x033C6220, String *, Marshal_PtrToStringAnsi, (void* ptr, MethodInfo * method)); 

DO_APP_FUNC(0x033C6240, String *, Marshal_PtrToStringUni, (void* ptr, MethodInfo * method)); 

DO_APP_FUNC(0x03502710, Type *, Type_GetType_3, (String* typeName, MethodInfo * method));


DO_APP_FUNC(0x033D8E90, Type *, Assembly_GetType, (Assembly * __this, String* name, bool throwOnError, MethodInfo * method)); 

DO_APP_FUNC(0x033D93B0, Assembly *, Assembly_LoadWithPartialName, (String* partialName, MethodInfo * method)); 

// Unity methods
DO_APP_FUNC(0x045067C0, GameObject *, GameObject_Find, (String* name, MethodInfo * method));


DO_APP_FUNC(0x0450D000, String *, Object_1_get_name, (Object_1* __this, MethodInfo * method));


DO_APP_FUNC(0x0450B750, Object_1 *, Object_1_FindObjectOfType, (Type* type, MethodInfo * method));


DO_APP_FUNC(0x0450B3D0, Object_1 *, Object_1_FindAnyObjectByType, (Type* type, MethodInfo * method));


DO_APP_FUNC(0x04566690, bool, Input_get_anyKey, (MethodInfo* method));



// Update loop to hook
DO_APP_FUNC(0x005F2F10, void, AudioManagerListenerPositionProvider_Update, (void* __this, MethodInfo* method));



// Autopilot
DO_APP_FUNC(0x0236B4E0, void, dnm_rmo, (dnm* __this, int64_t a, MethodInfo* method));

DO_APP_FUNC(0x0236A9A0, void, dnm_rml, (dnm* __this, int64_t a, bool b, MethodInfo* method));


// Click cell
DO_APP_FUNC(0x013B5600, void, InteractiveCellManager_moc, (InteractiveCellManager* __this, bool a, MethodInfo* method));

DO_APP_FUNC(0x013B4430, void, InteractiveCellManager_mnr, (InteractiveCellManager* __this, int32_t a, MethodInfo* method));


// Anti AFK
DO_APP_FUNC(0x011BAA50, void, InputChecker_Update, (InputChecker * __this, MethodInfo * method));
