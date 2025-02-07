/*
 * Stoat, a USI shogi engine
 * Copyright (C) 2025 Ciekce
 *
 * Stoat is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stoat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stoat. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "../../types.h"

#include <array>
#include <span>

#include "../../core.h"
#include "../../util/bits.h"
#include "../../util/multi_array.h"
#include "data.h"

namespace stoat::attacks::sliders {
    namespace bmi2 {
        extern const util::MultiArray<Bitboard, Colors::kCount, kLanceDataTableSize> g_lanceAttacks;

        [[nodiscard]] inline std::span<const Bitboard, kLanceDataTableSize> lanceAttacks(Color c) {
            assert(c);
            return g_lanceAttacks[c.idx()];
        }

        extern const std::array<Bitboard, kBishopData.tableSize> g_bishopAttacks;
        extern const std::array<Bitboard, kRookData.tableSize> g_rookAttacks;
    } // namespace bmi2

    [[nodiscard]] inline Bitboard lanceAttacks(Square sq, Color c, Bitboard occ) {
        const auto& sqData = lanceData(c).squares[sq.idx()];

        const usize idx = util::pext(occ.raw(), sqData.mask, sqData.shift);
        return bmi2::lanceAttacks(c)[sqData.offset + idx];
    }

    [[nodiscard]] inline Bitboard bishopAttacks(Square sq, Bitboard occ) {
        const auto& sqData = kBishopData.squares[sq.idx()];

        const usize idx = util::pext(occ.raw(), sqData.mask, sqData.shift);
        return bmi2::g_bishopAttacks[sqData.offset + idx];
    }

    [[nodiscard]] inline Bitboard rookAttacks(Square sq, Bitboard occ) {
        const auto& sqData = kRookData.squares[sq.idx()];

        const usize idx = util::pext(occ.raw(), sqData.mask, sqData.shift);
        return bmi2::g_rookAttacks[sqData.offset + idx];
    }
} // namespace stoat::attacks::sliders
