////////////////////////////////////////////////////////////////////////////
//
// Copyright 2015 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#ifndef REALM_TRANSACT_LOG_HANDLER_HPP
#define REALM_TRANSACT_LOG_HANDLER_HPP

#include <cstdint>
#include <realm/version_id.hpp>

namespace realm {
class BindingContext;
class SharedGroup;
enum class SchemaMode : uint8_t;

namespace _impl {
class NotifierPackage;
struct TransactionChangeInfo;

namespace transaction {
// Advance the read transaction version, with change notifications sent to delegate
// Must not be called from within a write transaction.
void advance(SharedGroup& sg, BindingContext* binding_context,
             SchemaMode schema_mode, NotifierPackage&);
void advance(SharedGroup& sg, BindingContext* binding_context,
             SchemaMode schema_mode, VersionID);

// Begin a write transaction
// If the read transaction version is not up to date, will first advance to the
// most recent read transaction and sent notifications to delegate
void begin(SharedGroup& sg, BindingContext* binding_context, SchemaMode schema_mode,
           NotifierPackage&);
void begin_without_validation(SharedGroup& sg);

// Commit a write transaction
void commit(SharedGroup& sg);

// Cancel a write transaction and roll back all changes, with change notifications
// for reverting to the old values sent to delegate
void cancel(SharedGroup& sg, BindingContext* binding_context);

// Advance the read transaction version, with change information gathered in info
void advance(SharedGroup& sg,
             TransactionChangeInfo& info,
             VersionID version=VersionID{});
} // namespace transaction
} // namespace _impl
} // namespace realm

#endif /* REALM_TRANSACT_LOG_HANDLER_HPP */
