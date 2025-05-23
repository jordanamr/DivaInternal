// C# methods
DO_APP_FUNC(0x03400CF0, String*, Marshal_PtrToStringAnsi, (void* ptr, MethodInfo* method));
DO_APP_FUNC(0x03400D10, String*, Marshal_PtrToStringUni, (void* ptr, MethodInfo* method));
DO_APP_FUNC(0x0353D1E0, Type*, Type_GetType_3, (String* typeName, MethodInfo* method));
DO_APP_FUNC(0x03413960, Type*, Assembly_GetType, (Assembly* __this, String* name, bool throwOnError, MethodInfo* method));
DO_APP_FUNC(0x03413E80, Assembly*, Assembly_LoadWithPartialName, (String* partialName, MethodInfo* method));

// Unity methods
DO_APP_FUNC(0x045412A0, GameObject*, GameObject_Find, (String* name, MethodInfo* method));
DO_APP_FUNC(0x04547AE0, String*, Object_1_get_name, (Object_1* __this, MethodInfo* method));
DO_APP_FUNC(0x04546230, Object_1*, Object_1_FindObjectOfType, (Type* type, MethodInfo* method));
DO_APP_FUNC(0x04545EB0, Object_1*, Object_1_FindAnyObjectByType, (Type* type, MethodInfo* method));
DO_APP_FUNC(0x045A1330, bool, Input_get_anyKey, (MethodInfo* method));

// Update loop to hook
DO_APP_FUNC(0x005EF770, void, AudioManagerListenerPositionProvider_Update, (void* __this, MethodInfo* method));

////// Autopilot
DO_APP_FUNC(0x023AA5A0, void, dnm_rmo, (dnm* __this, int64_t a, MethodInfo* method));
DO_APP_FUNC(0x023A3060, void, dnm_rml, (dnm* __this, int64_t a, bool b, MethodInfo* method));

// Click cell
DO_APP_FUNC(0x013C2FF0, void, InteractiveCellManager_moc, (InteractiveCellManager* __this, bool a, MethodInfo* method));
DO_APP_FUNC(0x013C1E20, void, InteractiveCellManager_mnr, (InteractiveCellManager* __this, int32_t a, MethodInfo* method));

// Anti AFK
DO_APP_FUNC(0x011CF5D0, void, InputChecker_Update, (InputChecker* __this, MethodInfo* method));