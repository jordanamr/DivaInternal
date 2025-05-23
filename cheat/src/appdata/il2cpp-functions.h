DO_APP_FUNC(0x033D1830, String*, Marshal_PtrToStringAnsi, (void* ptr, MethodInfo* method));
DO_APP_FUNC(0x033D1850, String*, Marshal_PtrToStringUni, (void* ptr, MethodInfo* method));
DO_APP_FUNC(0x0350DD20, Type*, Type_GetType_3, (String* typeName, MethodInfo* method));
DO_APP_FUNC(0x033E44A0, Type*, Assembly_GetType, (Assembly* __this, String* name, bool throwOnError, MethodInfo* method));
DO_APP_FUNC(0x033E49C0, Assembly*, Assembly_LoadWithPartialName, (String* partialName, MethodInfo* method));

// Unity methods
DO_APP_FUNC(0x04511DB0, GameObject*, GameObject_Find, (String* name, MethodInfo* method));
DO_APP_FUNC(0x045185F0, String*, Object_1_get_name, (Object_1* __this, MethodInfo* method));
DO_APP_FUNC(0x04516D40, Object_1*, Object_1_FindObjectOfType, (Type* type, MethodInfo* method));
DO_APP_FUNC(0x045169C0, Object_1*, Object_1_FindAnyObjectByType, (Type* type, MethodInfo* method));
DO_APP_FUNC(0x04571C80, bool, Input_get_anyKey, (MethodInfo* method));

// Update loop to hook
DO_APP_FUNC(0x005F26E0, void, AudioManagerListenerPositionProvider_Update, (void* __this, MethodInfo* method));

////// Autopilot
DO_APP_FUNC(0x02394B50, void, dnm_rmo, (dnm* __this, int64_t a, MethodInfo* method));
DO_APP_FUNC(0x02393FF0, void, dnm_rml, (dnm* __this, int64_t a, bool b, MethodInfo* method));

// Click cell
DO_APP_FUNC(0x013CF6E0, void, InteractiveCellManager_moc, (InteractiveCellManager* __this, bool a, MethodInfo* method));
DO_APP_FUNC(0x013CE510, void, InteractiveCellManager_mnr, (InteractiveCellManager* __this, int32_t a, MethodInfo* method));

// Anti AFK
DO_APP_FUNC(0x011DEA50, void, InputChecker_Update, (InputChecker* __this, MethodInfo* method));
