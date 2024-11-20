//
// Created by JIANG on 19/11/24.
//

#ifndef ENGINE_TAKEHOME_ORDER_STATUS_H
#define ENGINE_TAKEHOME_ORDER_STATUS_H

enum class OrderStatus {
    NEW,        // New
    PARTIAL,    // Partially filled
    FILLED,     // Filled
    CANCELED,   // Canceled
    REJECTED    // Rejected
};

class OrderStatusManager {
public:
    OrderStatusManager() {
        _status = OrderStatus::NEW;
    }
    void SetPartial() {
        _status = OrderStatus::PARTIAL;
    }
    void SetFilled() {
        _status = OrderStatus::FILLED;
    }
    void SetCanceled() {
        _status = OrderStatus::CANCELED;
    }
    void SetRejected() {
        _status = OrderStatus::REJECTED;
    }
    bool isNew() const {
        return _status == OrderStatus::NEW;
    }
    bool isPartial() const {
        return _status == OrderStatus::PARTIAL;
    }
    bool isFilled() const {
        return _status == OrderStatus::FILLED;
    }
    bool isCanceled() const {
        return _status == OrderStatus::CANCELED;
    }
    bool isRejected() const {
        return _status == OrderStatus::REJECTED;
    }
    OrderStatus getStatus() const {
        return _status;
    }
    std::string getStatusString() const {
        if (_status == OrderStatus::NEW) {
            return "NEW";
        } else if (_status == OrderStatus::PARTIAL) {
            return "PARTIAL";
        } else if (_status == OrderStatus::FILLED) {
            return "FILLED";
        } else if (_status == OrderStatus::CANCELED) {
            return "CANCELED";
        } else if (_status == OrderStatus::REJECTED) {
            return "REJECTED";
        } else {
            return "UNKNOWN";
        }
    }

private:
    OrderStatus _status;
};


#endif //ENGINE_TAKEHOME_ORDER_STATUS_H
