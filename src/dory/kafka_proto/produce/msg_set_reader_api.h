/* <dory/kafka_proto/produce/msg_set_reader_api.h>

   ----------------------------------------------------------------------------
   Copyright 2013-2014 if(we)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   ----------------------------------------------------------------------------

   API definition for message set reader abstraction.
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include <base/no_copy_semantics.h>
#include <dory/compress/compression_type.h>

namespace Dory {

  namespace KafkaProto {

    namespace Produce {

      class TMsgSetReaderApi {
        NO_COPY_SEMANTICS(TMsgSetReaderApi);

        public:
        class TBadMsgSet : public std::runtime_error {
          public:
          virtual ~TBadMsgSet() noexcept { }

          protected:
          explicit TBadMsgSet(const char *msg)
              : std::runtime_error(msg) {
          }
        };  // TBadMsgSet

        virtual ~TMsgSetReaderApi() noexcept { }

        virtual void Clear() = 0;

        /* Specify a buffer containing a message set to read. */
        virtual void SetMsgSet(const void *msg_set, size_t msg_set_size) = 0;

        virtual bool FirstMsg() = 0;

        virtual bool NextMsg() = 0;

        virtual bool CurrentMsgCrcIsOk() const = 0;

        virtual Compress::TCompressionType
        GetCurrentMsgCompressionType() const = 0;

        virtual const uint8_t *GetCurrentMsgKeyBegin() const = 0;

        virtual const uint8_t *GetCurrentMsgKeyEnd() const = 0;

        virtual const uint8_t *GetCurrentMsgValueBegin() const = 0;

        virtual const uint8_t *GetCurrentMsgValueEnd() const = 0;

        protected:
        TMsgSetReaderApi() = default;
      };  // TMsgSetReaderApi

    }  // Produce

  }  // KafkaProto

}  // Dory