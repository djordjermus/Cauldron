#include <string>

#include "cauldron-common/macro.autoOperator.h"
#include "cauldron-common/macro.coreManip.h"

#include "cauldron-common/primitives.h"
#include "cauldron-common/bounds.h"
#include "cauldron-common/callback.h"
#include "cauldron-common/eventData.h"

#include "cauldron-platform/key.h"
#include "paint.h"
#pragma once
namespace cauldron::gui {

	// Basic control
	class control {
		friend class ctrlint;
	public:
		using bounds_t = common::bounds2<i32>;
		using vector_t = common::vector2<i32>;

		class core_t;

		class state {
		public:
			class core_t;

			static const state hidden;
			static const state normal;
			static const state minimized;
			static const state maximized;

			state(core_t* core);
			INLINE_CORE_GET(core_t, _core);
			INLINE_CORE_CMP(state, core_t, _core);

		private:
			core_t* _core;
		};

		class style {
		public:
			class core_t;
			enum class option : u64 {
				none			= 0x00,
				bordered		= (1ull << 0ull),
				captioned		= (1ull << 1ull),	// REQUIRES BORDERED
				resizable		= (1ull << 2ull),	// INCOMPATIBLE WITH CHILD
				minimize_button	= (1ull << 3ull),	// REQUIRES CAPTIONED
				maximize_button	= (1ull << 4ull),	// REQUIRES CAPTIONED
				child			= (1ull << 5ull)	// INCOMPATIBLE WITH RESIZABLE AND BOREDERED
			};

			style(option options);
			INLINE_CORE_GET(core_t, _core);
			INLINE_CORE_CMP(style, core_t, _core);

			option getOptions() const;

		protected:
			style(core_t* core);

			static option coreToOptions(core_t* core);
			static core_t* optionsToCore(option options);
		private:
			core_t* _core;
		};

		class focusStyle {
		public:
			class core_t;

			// invalid focus state
			static const focusStyle invalid;
			// control accepts focus normally
			static const focusStyle focusable;
			// control rejects any attempt to focus on it
			static const focusStyle unfocusable;
			// control reject focus and send it to topmost child
			static const focusStyle defer_to_child;

			focusStyle();
			INLINE_CORE_GET(core_t, _core);
			INLINE_CORE_CMP(focusStyle, core_t, _core);

		private:
			focusStyle(core_t* core);
			core_t* _core = nullptr;
		};

		control();
		~control();

		// OPERATORS

		// Returns pointer to the core
		INLINE_CORE_GET(core_t, _core);
		INLINE_CORE_CMP(control, core_t, _core);
		// terminates the control
		virtual void terminate();
		// Repaints the control
		virtual void refresh();

		//
		// GETTERS

		// True if control is valid(i.e. still open)
		bool isValid() const;
		// Returns the bounds of the control relative to parent client area(or screen if no parent)
		bounds_t getBounds() const;
		// Returns the size of the client area
		vector_t getClientSize() const;
		// Returns the caption of the control
		std::wstring getCaption() const;

		// Returns pointer to the parent control; nullptr if no parent
		control* getParent() const;
		// Returns number of children
		i32 getChildCount() const;
		// Returns pointer to child under given index; nullptr if index out of bounds
		control* getChild(u32 index) const;

		// Returns state of the control - if window is not valid returns state::hidden
		state getState() const;
		// Returns state of the control - if window is not valid returns style::option::none
		style getStyle() const;
		// Returns focus style of the control - if window is not valid returns focusStyle::invalid
		focusStyle getFocusStyle() const;
		// Returns true if control is active - if window is not valid returns false
		bool isActive() const;
		// Returns true if control is focused - if window is not valid returns false
		bool isFocused() const;
		// Returns the opacity of the control
		f32 getOpacity() const;
		// Returns true if enabled
		bool isEnabled() const;
		// Returns true if cursor is over this control
		bool isCursorOver() const;
		// Returns true if control is double buffered
		bool isDoubleBuffered() const;

		//
		// SETTERS

		// Sets the bounds of the control
		// If surface is nonzero and state is state::hidden, state is updated to state::normal
		virtual void setBounds(const bounds_t& new_bounds);
		// Sets the caption of the control
		virtual void setCaption(const std::wstring& new_caption);
		// Adopts a child control
		virtual void adopt(control* adopt);
		// Disowns the child control
		virtual void disown(control* disown);
		// Sets new state
		virtual void setState(state new_state);
		// Sets new style
		virtual void setStyle(style new_style);
		// Sets new focus style
		virtual void setFocusStyle(focusStyle new_focus_style);
		// Sets active state
		virtual void setActive(bool active);
		// Sets focus state
		virtual void setFocus(bool focus);
		// Sets window opacity
		virtual void setOpacity(f32 opacity);
		// Sets enabled state
		virtual void setEnabled(bool enabled);
		// Sets double buffer usage
		virtual void setDoubleBuffered(bool double_buffered);

		//
		// EVENT HANDLER DATA
		
		class closeData : public common::eventData {};
		class terminateData : public common::eventData {};

		class activateData : public common::eventData {};
		class deactivateData : public common::eventData {};
		class gainFocusData : public common::eventData {};
		class loseFocusData : public common::eventData {};
		class enabledData : public common::eventData {};
		class disabledData : public common::eventData {};

		class changeParentData : public common::eventData {
		public:
			changeParentData(control* child, control* old_parent, control* new_parent);

			control* getChild() const;
			control* getOldParent() const;
			control* getNewParent() const;

		private:
			control* _child;
			control* _old_parent;
			control* _new_parent;
		};
		class adoptData : public changeParentData {
		public:
			adoptData(control* child, control* old_parent, control* new_parent);
		};
		class disownData : public changeParentData {
		public:
			disownData(control* child, control* old_parent, control* new_parent);
		};
		
		class moveData : public common::eventData {
		public:
			moveData(const vector_t& top_left);
			vector_t getTopLeft() const;

		private:
			vector_t _top_left;
		};
		class movingData : public common::eventData {
		public:
			movingData(bounds_t& ref_bounds);

			bounds_t getBounds() const;
			void setBounds(const bounds_t& final_bounds);

		private:
			bounds_t _bounds;
		};
		class sizeData : public common::eventData {
		public:
			sizeData(const vector_t& client_size);
			vector_t getClientSize() const;

		private:
			vector_t _client_size;
		};
		class sizingData : public common::eventData {
		public:
			enum class edge : u8 {
				none	= 0x00,
				left	= 0x01,
				top		= 0x02,
				right	= 0x04,
				bottom	= 0x08,
			};

			sizingData(bounds_t& ref_bounds, edge sized_edge);
			bounds_t getBounds() const;
			edge getSizedEdges() const;

			void setBounds(const bounds_t& final_bounds);
			
		private:
			bounds_t _bounds;
			edge _sized_edge;
		};

		class keyData : public common::eventData {
		public:
			keyData(key key);

			key getKey();

		private:
			key _key;
		};
		class keyDownData : public keyData {
		public:
			keyDownData(key key);
		};
		class keyUpData : public keyData {
		public:
			keyUpData(key key);
		};
		class characterData : public common::eventData {
		public:
			characterData(wch character);
			wch getChar() const;

		private:
			wch _character;
		};
		
		class cursorData : public common::eventData {
		public:
			cursorData(const vector_t& cursor_position);

			vector_t getCursorPos() const;

		private:
			vector_t _cursor_position;
		};
		class cursorEnterData : public cursorData {
		public:
			cursorEnterData(const vector_t& cursor_position);
		};
		class cursorMoveData : public cursorData {
		public:
			cursorMoveData(const vector_t& cursor_position);
		};
		class cursorLeaveData : public cursorData {
		public:
			cursorLeaveData(const vector_t& cursor_position);
		};
		class scrollData : public cursorData {
		public:
			scrollData(const vector_t& cursor_position, i32 scroll_distance);

			i32 getScrollDistance() const;

		private:
			i32 _scroll_distance;
		};
		
		class mouseData : public cursorData {
		public:
			mouseData(const vector_t& cursor_position, key button);
			key getButton();

		private:
			key _button;
		};
		class mouseDownData : public mouseData {
		public:
			mouseDownData(const vector_t& cursor_position, key button);
		};
		class mouseUpData : public mouseData {
		public:
			mouseUpData(const vector_t& cursor_position, key button);
		};
		class doubleClickData : public mouseData {
		public:
			doubleClickData(const vector_t& cursor_position, key button);
		};

		class paintData : public common::eventData {
		public:
			paintData(paint& paint);

			paint& getPaint() const;

		private:
			paint& _paint;
		};


		//
		// EVENT HANDLERS

		common::observable<void, control&, closeData&>& onClose();
		common::observable<void, control&, terminateData&>& onTerminate();

		common::observable<void, control&, activateData&>& onActivate();
		common::observable<void, control&, deactivateData&>& onDeactivate();
		common::observable<void, control&, gainFocusData&>& onGainFocus();
		common::observable<void, control&, loseFocusData&>& onLoseFocus();
		common::observable<void, control&, enabledData&>& onEnabled();
		common::observable<void, control&, disabledData&>& onDisabled();

		common::observable<void, control&, changeParentData&>& onChangeParent();
		common::observable<void, control&, adoptData&>& onAdopt();
		common::observable<void, control&, disownData&>& onDisown();

		common::observable<void, control&, moveData&>& onMove();
		common::observable<void, control&, movingData&>& onMoving();
		common::observable<void, control&, sizeData&>& onSize();
		common::observable<void, control&, sizingData&>& onSizing();

		common::observable<void, control&, keyDownData&>& onKeyDown();
		common::observable<void, control&, keyUpData&>& onKeyUp();
		common::observable<void, control&, characterData&>& onCharacter();

		common::observable<void, control&, cursorEnterData&>& onCursorEnter();
		common::observable<void, control&, cursorMoveData&>& onCursorMove();
		common::observable<void, control&, cursorLeaveData&>& onCursorLeave();

		common::observable<void, control&, scrollData&>& onScroll();

		common::observable<void, control&, mouseDownData&>& onMouseDown();
		common::observable<void, control&, mouseUpData&>& onMouseUp();
		common::observable<void, control&, doubleClickData&>& onDoubleClick();

		common::observable<void, control&, paintData&>& onPaint();

		//
		// Helper

		static void terminateOnClose(control& sender, closeData& e);
		static bounds_t adjustBoundsForStyle(
			const bounds_t& original, 
			style style);
		static void debugHandler(control& sender, paintData& e);
		template<class eventData_t>
		static void refreshOnEvent(control& sender, eventData_t& e) { sender.refresh(); };
		//static void limitWidth();
	private:
		core_t* _core =
			nullptr;
		control* _parent =
			nullptr;
		std::vector<control*> _children =
			std::vector<control*>();

		state _state =
			state::hidden;
		style _style =
			style::option::none;

		focusStyle _focus_style =
			focusStyle::invalid;

		bool _cursor_inside =
			false;
		bool _double_buffered =
			false;
		bool _enabled =
			true;

		gui::paint::bitmap _backbuffer;
		void adjustBackbufferSize();

		common::observable<void, control&, closeData&>			_on_close =
			common::observable<void, control&, closeData&>();
		common::observable<void, control&, terminateData&>		_on_terminate =
			common::observable<void, control&, terminateData&>();

		common::observable<void, control&, activateData&>		_on_activate =
			common::observable<void, control&, activateData&>();
		common::observable<void, control&, deactivateData&>		_on_deactivate =
			common::observable<void, control&, deactivateData&>();
		common::observable<void, control&, gainFocusData&>		_on_gainFocus =
			common::observable<void, control&, gainFocusData&>();
		common::observable<void, control&, loseFocusData&>		_on_loseFocus =
			common::observable<void, control&, loseFocusData&>();
		common::observable<void, control&, enabledData&>		_on_enabled =
			common::observable<void, control&, enabledData&>();
		common::observable<void, control&, disabledData&>		_on_disabled =
			common::observable<void, control&, disabledData&>();

		common::observable<void, control&, changeParentData&>	_on_change_parent =
			common::observable<void, control&, changeParentData&>();
		common::observable<void, control&, adoptData&>			_on_adopt =
			common::observable<void, control&, adoptData&>();
		common::observable<void, control&, disownData&>			_on_disown =
			common::observable<void, control&, disownData&>();

		common::observable<void, control&, moveData&>			_on_move =
			common::observable<void, control&, moveData&>();
		common::observable<void, control&, movingData&>			_on_moving =
			common::observable<void, control&, movingData&>();
		common::observable<void, control&, sizeData&>			_on_size =
			common::observable<void, control&, sizeData&>();
		common::observable<void, control&, sizingData&>			_on_sizing =
			common::observable<void, control&, sizingData&>();

		common::observable<void, control&, keyDownData&>		_on_key_down =
			common::observable<void, control&, keyDownData&>();
		common::observable<void, control&, keyUpData&>			_on_key_up =
			common::observable<void, control&, keyUpData&>();
		common::observable<void, control&, characterData&>		_on_character =
			common::observable<void, control&, characterData&>();

		common::observable<void, control&, cursorEnterData&>	_on_cursor_enter =
			common::observable<void, control&, cursorEnterData&>();
		common::observable<void, control&, cursorMoveData&>		_on_cursor_move =
			common::observable<void, control&, cursorMoveData&>();
		common::observable<void, control&, cursorLeaveData&>	_on_cursor_leave =
			common::observable<void, control&, cursorLeaveData&>();

		common::observable<void, control&, scrollData&>			_on_scroll =
			common::observable<void, control&, scrollData&>();

		common::observable<void, control&, mouseDownData&>		_on_mouse_down =
			common::observable<void, control&, mouseDownData&>();
		common::observable<void, control&, mouseUpData&>		_on_mouse_up =
			common::observable<void, control&, mouseUpData&>();
		common::observable<void, control&, doubleClickData&>	_on_double_click =
			common::observable<void, control&, doubleClickData&>();

		common::observable<void, control&, paintData&>			_on_paint =
			common::observable<void, control&, paintData&>();

		control(const control& copy) = delete;
		control& operator=(const control& copy) = delete;
		control(control&& move) = delete;
		control& operator=(control&& move) = delete;
	};

	INLINE_BITWISE_OR(control::style::option);
	INLINE_BITWISE_AND(control::style::option);
	INLINE_BITWISE_XOR(control::style::option);

	INLINE_BITWISE_OR(control::sizingData::edge);
	INLINE_BITWISE_AND(control::sizingData::edge);
	INLINE_BITWISE_XOR(control::sizingData::edge);
}