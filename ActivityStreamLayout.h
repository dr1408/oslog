#ifndef OSLOG_ACTIVITY_STREAM_LAYOUT_H
#define OSLOG_ACTIVITY_STREAM_LAYOUT_H

#include <stddef.h>
#include <stdint.h>
#include "ActivityStreamAPI.h"

// Verified against LoggingSupport on iOS 27.2 / 24B5089g. Its callback prefix
// has an additional 32-bit UID at +0x10 and 4-byte packing. Root/mobile
// records contain 0/501 there; Apple's versioned decoder calls the field uid.
// Pass the message to Apple's formatter without decoding its legacy fields.
struct __attribute__((packed, aligned(4))) oslog_entry_prefix_ios27 {
    os_activity_stream_type_t type;
    pid_t pid;
    uint64_t proc_id;
    uid_t uid;
    const uint8_t *proc_imageuuid;
    const char *proc_imagepath;
    os_activity_id_t activity_id;
    os_activity_id_t parent_id;
};

static_assert(sizeof(oslog_entry_prefix_ios27) == 0x34,
              "iOS 27 message must begin at entry + 0x34");
static_assert(offsetof(oslog_entry_prefix_ios27, pid) ==
              offsetof(os_activity_stream_entry_s, pid),
              "PID must remain readable using the existing prefix");

static inline os_log_message_t oslog_message_at(os_activity_stream_entry_t entry,
                                               size_t offset) {
    return reinterpret_cast<os_log_message_t>(
        reinterpret_cast<uint8_t *>(entry) + offset);
}

#endif
