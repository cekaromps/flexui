#include <flexui/FlexLayout.h>

void FlexBox::Add(FlexChild child) {
    children.push_back(child);
}

std::vector<FlexBox::LayoutResult> FlexBox::ComputeLayout(Rectangle bounds) {
    bool  isRow         = direction == FlexDirection::Row;
    float mainAxisSize  = isRow ? bounds.width  : bounds.height;
    float crossAxisSize = isRow ? bounds.height : bounds.width;
    int n = 0;
    for(auto& c : children)
        if(c.visible) n++;

    float totalFixed = 0, totalGrow = 0;
    for (auto& c : children) {
        float fixedMain = isRow ? c.fixedW : c.fixedH;
        if (fixedMain >= 0) totalFixed += fixedMain;
        else totalGrow += (c.grow > 0 ? c.grow : 1);
    }

    float totalGap  = gap * (n > 0 ? n - 1 : 0);
    float remaining = mainAxisSize - totalFixed - totalGap - padding * 2;
    if (remaining < 0) remaining = 0;

    float cursor = isRow ? bounds.x + padding : bounds.y + padding;

    if (totalGrow == 0) {
        if      (justify == FlexJustify::Center) cursor += remaining / 2;
        else if (justify == FlexJustify::End)    cursor += remaining;
    }

    float spaceBetweenExtra = 0;
    if (justify == FlexJustify::SpaceBetween && n > 1 && totalGrow == 0)
        spaceBetweenExtra = remaining / (n - 1);

    std::vector<LayoutResult> results;

    for (auto& c : children) {
        float fixedMain = isRow ? c.fixedW : c.fixedH;
        float mainSize  = fixedMain >= 0
            ? fixedMain
            : remaining * ((c.grow > 0 ? c.grow : 1) / totalGrow);

        float crossFixed = isRow ? c.fixedH : c.fixedW;
        float crossSize  = (align == FlexAlign::Stretch || crossFixed < 0)
            ? crossAxisSize - padding * 2
            : crossFixed;

        float crossPos = isRow ? bounds.y + padding : bounds.x + padding;
        if      (align == FlexAlign::Center) crossPos += (crossAxisSize - padding * 2 - crossSize) / 2;
        else if (align == FlexAlign::End)    crossPos += (crossAxisSize - padding * 2 - crossSize);

        Rectangle childRect = isRow
            ? Rectangle{cursor, crossPos, mainSize, crossSize}
            : Rectangle{crossPos, cursor, crossSize, mainSize};

        results.push_back({childRect});
        cursor += mainSize + gap + spaceBetweenExtra;
    }

    return results;
}

void FlexBox::Layout(Rectangle bounds) {
    auto results = ComputeLayout(bounds);
    for (int i = 0; i < (int)children.size(); i++)
        if (children[i].visible && children[i].draw)
            children[i].draw(results[i].rect);
}

void FlexBox::HandleInput(Rectangle bounds) {
    auto results = ComputeLayout(bounds);
    for (int i = 0; i < (int)children.size(); i++)
        if (children[i].visible && children[i].handleInput)
            children[i].handleInput(results[i].rect);
}


