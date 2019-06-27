#pragma once

namespace winrt::Microsoft::React
{
	/// <summary>
	/// An enumeration to signify the current lifecycle state for a 
	/// <see cref="ReactInstanceManager"/>.
	/// </summary>
	enum struct LifecycleState
	{
		/// <summary>
		/// Lifecycle state before an application is initially created.
		/// </summary>
		BeforeCreate,

		/// <summary>
		/// Lifecycle state before an application is resumed.
		/// </summary>
		Suspended,

		/// <summary>
		/// Lifecycle state of a foreground running application.
		/// </summary>
		Foreground,

		/// <summary>
		/// Lifecycle state when the application is in the background.
		/// </summary>
		Background,
	};
}
