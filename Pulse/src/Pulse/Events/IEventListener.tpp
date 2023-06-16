namespace Pulse::Events {

    template<Pulse::Utility::CRTPConform Derived>
    IEventListener<Derived>::~IEventListener() {
        if (!isClean_) {
#pragma warning(push)
#pragma warning(disable: 4297)
            throw std::runtime_error("IEventListener is not clean. Please call Cleanup() before destroying the object."); // TODO: automate this in a parent script that is like MonoBehaviour in Unity
#pragma warning(pop)
        }
    }

    template<Pulse::Utility::CRTPConform Derived>
    void IEventListener<Derived>::_Cleanup() {
        auto self_shared_ptr = this->_get_shared_from_this();
        if (self_shared_ptr) {
            for (auto& eventIterator : eventPointers_) {
                eventIterator.second->_RemoveListener(self_shared_ptr, eventIterator.first);
            }
        }
        isClean_ = true;
    }

    template <Pulse::Utility::CRTPConform Derived>
    template <typename... Args>
    EventListenerID IEventListener<Derived>::AddListener(std::shared_ptr<Event<Args...>> event, void(Derived::* callback)(Args...), bool isThreadsafe) {
        EventListenerID eventListenerID = event->_AddListener(_get_shared_from_this(),std::make_shared<Internal::EventListenerMember<Derived, Args...>>(static_cast<Derived*>(this), callback, isThreadsafe));
        EventID eventID = event->_GetEventID();

        eventToListeners_[eventID].insert(eventListenerID);
        eventPointers_[eventID] = event;
        listenersAndEvents_[eventListenerID] = eventID;

        return eventListenerID;
    }

    template <Pulse::Utility::CRTPConform Derived>
    template <typename... Args>
    EventListenerID IEventListener<Derived>::AddListener(std::shared_ptr<Event<Args...>> event, void(*callback)(Args...), bool isThreadsafe) {
        EventListenerID eventListenerID = event->AddListener(_get_shared_from_this(), std::make_shared<Internal::EventListenerNoMember<Args...>>(callback, isThreadsafe));
        EventID eventID = event->_GetEventID();

        eventToListeners_[eventID].insert(eventListenerID);
        eventPointers_[eventID] = event;
        listenersAndEvents_[eventListenerID] = eventID;

        return eventListenerID;
    }

    template <Pulse::Utility::CRTPConform Derived>
    template <typename Functor, typename... Args>
    EventListenerID IEventListener<Derived>::AddListener(std::shared_ptr<Event<Args...>> event, Functor&& callback, bool isThreadsafe) {
        EventListenerID eventListenerID = event->AddListener(_get_shared_from_this(), std::make_shared<Internal::EventListenerNoMember<Args...>>(std::forward<Functor>(callback, isThreadsafe)));
        EventID eventID = event->_GetEventID();

        eventToListeners_[eventID].insert(eventListenerID);
        eventPointers_[eventID] = event;
        listenersAndEvents_[eventListenerID] = eventID;

        return eventListenerID;
    }

} // namespace Pulse::Events