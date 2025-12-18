#pragma once

class Profile;

// Behavioral Pattern: Observer for profile updates.
class ProfileObserver {
public:
    virtual ~ProfileObserver() = default;
    virtual void onProfileUpdated(const Profile& profile) = 0;
};
