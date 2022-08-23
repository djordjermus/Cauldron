#include "../anchoredControl.h"
#include "cauldron-common/bounds.ostream.h"
#include <iostream>
#include <windows.h>
namespace cauldron::gui {
	using namespace cauldron::common;



	anchoredControl::anchoredControl() : control(), _anchor(), _offset() {
		onChangeParent().subscribe(
			callback<void, control&, changeParentData&>::
			make<anchoredControl, &anchoredControl::recalcBoundsOnParentChanged>(this));
		onTerminate().subscribe(
			callback<void, control&, terminateData&>::
			make<anchoredControl, &anchoredControl::onTerminateAnchored>(this));
	}

	bounds2<f32> anchoredControl::getAnchor() const {
		return _anchor;
	}
	bounds2<f32> anchoredControl::getOffset() const {
		return _offset;
	}
	bounds2<f32> anchoredControl::getMargins() const {
		return bounds2<f32>(_offset.from.x, _offset.from.y, -_offset.to.x, -_offset.to.y);
	}

	// SETTERS

	void anchoredControl::setAnchor(const bounds2<f32>& new_anchor) {
		_anchor = new_anchor;
		recalculateBounds();
	}
	void anchoredControl::setOffset(const bounds2<f32>& new_offset) {
		_offset = new_offset;
		recalculateBounds();
	}
	void anchoredControl::setMargins(const bounds2<f32>& new_margins) {
		_offset.from	= new_margins.from;
		_offset.to		= -new_margins.to;
		recalculateBounds();
	}
	void anchoredControl::setBounds(const bounds2<i32>& new_bounds) {
		control* parent = getParent();
		if (parent) {
			bounds2<i32> frame =
				bounds2<i32>({ 0, 0 }, getParent()->getClientSize());
			setOffset(boundsToOffset(frame, _anchor, new_bounds));
		}
	}

	void anchoredControl::recalculateBounds() {
		control* parent = getParent();
		if (parent == nullptr) 
			return;

		bounds2<i32> frame =
			bounds2<i32>({0, 0}, parent->getClientSize());
		bounds2<i32> new_bounds = calculateBounds(frame, _anchor, _offset);
		this->control::setBounds(new_bounds);
	}

	bounds2<i32> anchoredControl::calculateBounds(
		const bounds2<i32>& frame,
		const bounds2<f32>& anchor,
		const bounds2<f32>& offset) {
		bounds2<i32> ret = {};
		auto size = frame.size();

		ret.from.x	= size.x * anchor.from.x + offset.from.x;
		ret.from.y	= size.y * anchor.from.y + offset.from.y;
		ret.to.x	= size.x * anchor.to.x + offset.to.x;
		ret.to.y	= size.y * anchor.to.y + offset.to.y;

		return ret;
	}
	bounds2<i32> anchoredControl::boundsToOffset(
		const bounds2<i32>& frame,
		const bounds2<f32>& anchor,
		const bounds2<f32>& bounds) {

		bounds2<i32> ret = {};
		auto size = frame.size();

		ret.from.x	= bounds.from.x - size.x * anchor.from.x;
		ret.from.y	= bounds.from.y - size.y * anchor.from.y;
		ret.to.x	= bounds.to.x - size.x * anchor.to.x;
		ret.to.y	= bounds.to.y - size.y * anchor.to.y;

		return ret;
	}

	void anchoredControl::recalcBoundsOnParentSize(control& sender, sizeData& e) {
		bounds2<i32> old_bounds = getBounds();
		bounds2<i32> new_bounds = calculateBounds({ {}, e.getClientSize() }, _anchor, _offset);
		if(old_bounds != new_bounds)
			this->control::setBounds(new_bounds);
	}
	void anchoredControl::recalcBoundsOnParentSizing(control& sender, sizingData& e) {
		bounds2<i32> old_bounds = getBounds();
		bounds2<i32> new_bounds = calculateBounds({ {}, sender.getClientSize() }, _anchor, _offset);
		if (old_bounds != new_bounds)
			this->control::setBounds(new_bounds);
	}

	void anchoredControl::recalcBoundsOnParentChanged(control& sender, changeParentData& e) {
		if (e.getOldParent() != nullptr) {
			e.getOldParent()->onSize().unsubscribe(
				callback<void, control&, sizeData&>::
				make<anchoredControl, &anchoredControl::recalcBoundsOnParentSize>(this));
		}
		if (e.getNewParent() != nullptr) {
			e.getNewParent()->onSize().subscribe(
				callback<void, control&, sizeData&>::
				make<anchoredControl, &anchoredControl::recalcBoundsOnParentSize>(this));
		}
	}
	void anchoredControl::onTerminateAnchored(control& sender, terminateData& e) {
		control* parent = sender.getParent();
		if (parent != nullptr) {
			parent->onSize().unsubscribe(
				callback<void, control&, sizeData&>::
				make<anchoredControl, &anchoredControl::recalcBoundsOnParentSize>(this));
		}
	}
}