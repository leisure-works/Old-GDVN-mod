#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <string>

namespace ix {
class WebSocket;
}

class WebsocketClient : public std::enable_shared_from_this<WebsocketClient> {
  public:
    using OpenCallback = std::function<void()>;
    using MessageCallback = std::function<void(std::string const&)>;
    using CloseCallback = std::function<void()>;

    struct Callbacks {
        OpenCallback onOpen;
        MessageCallback onMessage;
        CloseCallback onClose;
    };

    WebsocketClient();
    virtual ~WebsocketClient();

    virtual void update(float dt);
    virtual void close();
    bool isOpen() const;

  protected:
    bool connectSocket(std::string url, Callbacks callbacks);
    bool isClosed() const;
    bool hasSocket() const;
    void sendText(std::string const& text);

  private:
    std::unique_ptr<ix::WebSocket> m_socket;
    Callbacks m_callbacks;
    mutable std::mutex m_callbackMutex;
    std::atomic_bool m_open = false;
    std::atomic_bool m_closed = false;
    std::atomic_bool m_userClosed = false;

    void handleSocketOpen();
    void handleSocketMessage(std::string const& message);
    void handleSocketClosed();
    Callbacks callbacks() const;
    void clearCallbacks();
};
