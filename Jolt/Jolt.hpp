// Force Feedback (a.k.a. Haptic) Support Abstraction Layer
// -	Win32 is supported through Microsoft DirectX 8
//	DirectX 8 still works on Windows XP, so I'm not attempting to support a higher version for now.
//	Ref: http://msdn.microsoft.com/en-us/library/windows/desktop/ee417563%28v=vs.85%29.aspx
// -	Currently, SDL does not support haptic devices. So this is Win32 only.
// Copyright Chris White.
// See License.txt for more details.
#pragma once

// Function prototypes
// ───────────────────
namespace forcefeedback {
extern bool init(int max_force, int min_force, int force_duration);
extern void close();
extern int set(int xdirection, int force);
extern bool is_supported();
} // namespace forcefeedback
