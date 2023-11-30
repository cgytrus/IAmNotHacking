#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/PlayLayer.hpp>
class $modify(PlayLayer) {
    void showEndLayer() {
        PlayLayer::showEndLayer();
        if (m_isPracticeMode || m_level->m_stars < 8 || m_level->m_attempts >= 10 && m_level->m_jumps >= 50)
            return;
        bool antiAtts = m_level->m_attempts < 10;
        bool antiJumps = m_level->m_jumps < 50;
        auto attsText = fmt::format("<cg>{}</c> {}", m_level->m_attempts.value(), m_level->m_attempts == 1 ? "attempt" : "attempts");
        auto jumpsText = fmt::format("<cb>{}</c> {}", m_level->m_jumps.value(), m_level->m_jumps == 1 ? "jump" : "jumps");
        geode::createQuickPopup(
            "Anti-cheat Warning",
            fmt::format(
                "You have only achieved {} in this level, "
                "which will make its progress <cr>reset</c> once you <co>save</c> your progress to the cloud.\n"
                "Do you want to <cy>alter</c> your current amount of {} to prevent that?",
                antiAtts ? antiJumps ? fmt::format("{} and {}", attsText, jumpsText) : attsText : jumpsText,
                antiAtts ? antiJumps ? "<cg>attempts</c> and <cb>jumps</c>" : "<cg>attempts</c>" : "<cb>jumps</c>"
            ),
            "No",
            "Yes",
            420.f,
            [this](FLAlertLayer* layer, bool btn2) {
                if (!btn2)
                    return;
                if (m_level->m_attempts < 10)
                    m_level->m_attempts = 10;
                if (m_level->m_jumps < 50)
                    m_level->m_jumps = 50;
            }
        );
    }
};
