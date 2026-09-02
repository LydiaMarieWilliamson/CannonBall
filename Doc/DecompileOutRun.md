<font size=+0>

# Decompilation Of OutRun

*	[OutRun Games And CannonBall Races And Movies](#Session1)
*	[The Addressing And Layout Of The ROMs](#Session2)
*	[Fixing A Hidden Character Code Bug](#Session3)

<a name=session1></a>
# OutRun Games And CannonBall Races And Movies

<hr/>

<font color=blue>

> Has there ever been a Eurasian, African or Latin American version of the 1970's U.S. Cannonball runs?

</font>

Yes—although nothing became quite as famous or culturally influential as the U.S. **Cannonball Baker Sea-to-Shining-Sea Memorial Trophy Dash** (1971–1979), there have been a number of similar illegal or semi-legal long-distance endurance runs on other continents.

### Europe / Eurasia

Europe has probably had the closest equivalents.

* Cannonball Europe (2000s–present)

  * An underground rally inspired directly by the American Cannonball.
  * Routes have crossed multiple countries, often from western Europe to eastern Europe.
  * Participants generally avoid motorways when necessary, use spotters and GPS, and often drive supercars.

* Gumball 3000

  * Founded in 1999.
  * Unlike the original Cannonball, it is **not a race**.
  * It is a celebrity charity rally conducted with permits and official events.
  * Nevertheless, some participants have been arrested for excessive speeding.

* Baltic Sea Circle Rally

  * A legal endurance adventure around northern Europe.
  * Emphasizes navigation and endurance rather than outright speed.

### Russia / Eurasia

Russia has seen numerous unofficial "cross-Russia" speed records, especially:

* Trans-Siberian Highway crossings.
* Moscow to Vladivostok attempts.

These have generally been private record attempts rather than organized races. The enormous distances (roughly 9,000 km by road), changing road quality, and legal risks have kept them relatively obscure.

### Latin America

There has never been a famous continent-wide Cannonball equivalent, but there have been occasional endurance challenges:

* Attempts to drive sections or all of the Pan-American Highway as quickly as possible.
* Private record attempts between cities such as Mexico City and Buenos Aires.
* Various amateur rallies across countries like Argentina, Chile, and Brazil.

The main obstacle is the Darién Gap, which interrupts the Pan-American Highway, requiring vehicles to be shipped between Panama and Colombia.

### Africa

Africa has almost no true Cannonball tradition.

Reasons include:

* Vast stretches of undeveloped roads.
* Numerous international border crossings.
* Political instability in some regions.
* Safety concerns.
* Large differences in road conditions.

Instead, Africa became known for legal endurance rallies such as:

* East African Safari Rally
* Africa Eco Race

These test endurance over long distances but are organized competitions rather than illegal point-to-point speed runs.

### Why the U.S. Cannonball was unique

The original 1970s Cannonball worked because the United States had a combination that few other places did:

* A nearly continuous interstate highway system.
* Thousands of miles without international borders.
* Comparatively light traffic in much of the country at the time.
* A car culture that celebrated grand touring and high-speed driving.
* A recognizable coast-to-coast route that could be repeated and compared.

Europe's dense borders and traffic, Latin America's infrastructure gaps, and Africa's road and border challenges made direct equivalents much harder to sustain.

So if you're looking for the closest analogues by region:

* **Europe:** Cannonball Europe is the nearest spiritual successor, with Gumball 3000 as its legal, high-profile cousin.
* **Russia/Eurasia:** Private cross-country record attempts on the Trans-Siberian Highway.
* **Latin America:** Isolated Pan-American Highway endurance attempts, but no enduring organized Cannonball tradition.
* **Africa:** Essentially no comparable illegal cross-continental speed run; organized endurance rallies have filled that niche instead.

[Reply Link](https://chatgpt.com/s/t_6a418dd908b88191bb37964c76b5c56a)

<hr/>

<font color=blue>

> OutRun and OutRunners look like they were inspired by these races - particularly the Cannonball Run and the associated movies.

</font>

That's a widely shared interpretation, and there's good reason for it. While Sega has never explicitly said that Out Run was based on the Cannonball races or films, the similarities are striking.

Some of the strongest parallels include:

* **The fantasy of a cross-country dash.** Like the original Cannonball Baker Sea-to-Shining-Sea Memorial Trophy Dash, *Out Run* isn't about completing laps—it's about driving across a continent as quickly as possible through varied scenery.

* **Exotic sports cars.** The player's car in *Out Run* is an unmistakable homage to the Ferrari Testarossa (with altered styling because Sega did not initially have a Ferrari license). The Cannonball races and their film adaptations were famous for featuring Ferraris, Lamborghinis, Porsches, and other high-performance cars.

* **Scenic variety.** Both the game and the Cannonball concept celebrate the journey: coastlines, mountains, deserts, forests, and cities rather than a closed racing circuit.

* **Style over realism.** The appeal isn't strict motorsport simulation. It's the fantasy of freedom, speed, and adventure—an ethos shared by the games and the movies.

OutRunners arguably leans even further into that aesthetic. It adds:

* Multiple colorful teams.
* A wide range of over-the-top vehicles.
* Rival drivers with exaggerated personalities.
* A playful, globe-trotting atmosphere.

That ensemble feel is reminiscent of the ensemble casts in films like The Cannonball Run and Cannonball Run II, where the entertainment comes as much from the colorful competitors and their antics as from who finishes first.

It's also worth noting that *Out Run*'s director, Yu Suzuki, has said his goal was to create the feeling of taking a luxurious road trip through Europe in a Ferrari with a companion, rather than to simulate competitive racing. That emphasis on the *experience* of a high-speed grand tour aligns closely with the romanticized image of the Cannonball, even if it wasn't a direct adaptation.

So while there isn't an official statement that "*Out Run* was inspired by the Cannonball Run," it's fair to say the game emerged from the same cultural moment that celebrated exotic cars, long-distance road adventures, and stylish, carefree driving. The Cannonball races and especially their popular film adaptations helped make that fantasy familiar to audiences in the late 1970s and early 1980s, making them a plausible influence on the atmosphere and tone of the *Out Run* series.

[Reply Link](https://chatgpt.com/s/t_6a418decd33481919b2b769965b04fd6)

<hr/>

<font color=blue>

> What CPU's were OutRun and OutRunner on in the arcade and console versions? I see ROM's out there, as well as an outright translation into C++ (called CannonBall)?

</font>

Interestingly, the connection to *The Cannonball Run* is stronger than many people realize. Yu Suzuki later confirmed that his original concept for *Out Run* **was inspired by the 1981 film** The Cannonball Run, although he transformed it into a more romantic, scenic driving experience rather than a race full of crashes and gimmicks. ([Wikipedia][1])

As for the hardware:

| Version          | Main CPU(s)                     | Sound CPU               |
| ---------------- | ------------------------------- | ----------------------- |
| Out Run (Arcade) | **2 × Motorola 68000 @ 10 MHz** | **Zilog Z80 @ 4 MHz**   |
| OutRunners       | **NEC V70 (32-bit) @ 20 MHz**   | **Zilog Z80 @ 8.1 MHz** |

The original *Out Run* hardware was extraordinary for 1986. Instead of one 68000 like many arcade games, Sega used **two**:

* One 68000 handled the gameplay, AI, and game logic.
* The second 68000 handled sprite generation, road calculations, and graphics coordination.
* A Z80 drove the music and sound effects through a Yamaha YM2151 FM synthesizer and Sega PCM sample hardware. ([PixelatedArcade][2])

That hardware is why *Out Run* looked so far ahead of its contemporaries.

### Home console CPUs

The home versions naturally varied a lot:

| Platform   | CPU                                        |
| ---------- | ------------------------------------------ |
| Out Run    | Zilog Z80 @ 3.58 MHz                       |
| Out Run    | Motorola 68000 @ 7.67 MHz + Z80 for sound  |
| Out Run    | Hudson HuC6280 (65C02-derived) @ ~7.16 MHz |
| OutRunners | Motorola 68000 + Z80                       |

The Genesis/Mega Drive version is particularly impressive because its 68000 is from the same family as the arcade board's CPUs, just with only **one** processor instead of two and much less graphics hardware.

### About CannonBall

Yes—and it's one of the most fascinating reverse-engineering projects in retro gaming.

CannonBall is **not an emulator** like MAME.

Instead, its author, Chris White ("reassembler"), spent years reverse-engineering the original arcade code and rewrote the entire game engine in portable C++. It still requires the original *Out Run* arcade ROMs because those ROMs contain the copyrighted game assets (graphics, music, sounds, and data), but the executable itself is a modern native engine. ([Sonic Retro Forums][3])

That approach lets CannonBall add features the original hardware couldn't easily support, including:

* True 60 FPS gameplay on modern systems
* Native widescreen rendering
* High-resolution output
* Force-feedback wheel support
* Time Trial and Continuous modes
* Custom tracks
* Numerous bug fixes and quality-of-life improvements ([GitHub][4])

It's conceptually similar to projects like:

* OpenRCT2
* OpenTTD
* OpenMW

These aren't emulators—they're clean-room or reverse-engineered engines that use the original game data.

For anyone interested in classic arcade hardware, CannonBall is especially valuable because it documents how Sega achieved *Out Run*'s famous "Super Scaler" effects in software, making one of the most influential arcade racing engines ever built much easier to study than trying to decipher thousands of lines of 68000 assembly.

[1]: https://en.wikipedia.org/wiki/Out_Run?utm_source=chatgpt.com "Out Run"
[2]: https://pixelatedarcade.com/games/outrun/techspecs?utm_source=chatgpt.com "OutRun technical specs - PixelatedArcade"
[3]: https://forums.sonicretro.org/index.php?threads%2Fcannonball-enhanced-outrun-engine-released.30357%2F=&utm_source=chatgpt.com "Cannonball - Enhanced OutRun Engine Released | Sonic and Sega Retro Forums"
[4]: https://github.com/djyt/cannonball/wiki?utm_source=chatgpt.com "Home · djyt/cannonball Wiki · GitHub"

[Reply Link](https://chatgpt.com/s/t_6a418e03f8a88191a3c90fbbe51715b8)

<hr/>

<font color=blue>

> The C++ translation requires external ROM's in what sense? Actual code - decompiled or run in the C++ program, or what?

</font>

Good question. The short answer is: **the ROMs are used as data, not as executable code.** That's the key distinction between CannonBall and an emulator like MAME.

Think of it this way:

### MAME

```
68000 ROM (machine code)
        │
        ▼
68000 CPU emulator
        │
        ▼
Game runs exactly as original hardware
```

The original 68000 instructions are fetched from the ROM and executed (via emulation).

---

### CannonBall

```
C++ engine (native x86/ARM executable)
        │
        ├── reads sprite ROMs
        ├── reads road data
        ├── reads music/sample ROMs
        ├── reads track layouts
        └── reads lookup tables
```

The original **68000 machine code is never executed.**

Instead, Chris White reverse-engineered what the assembly *did* and reimplemented that logic in C++.

For example, instead of:

```asm
MOVE.W D0,$1234
ADD.W  D1,D0
BNE    ...
```

he wrote something conceptually like:

```cpp
player.speed += acceleration;
road.update(player.position);
traffic.tick();
```

Those C++ functions replace the original assembly entirely.

---

## So why are the ROMs still needed?

Because they contain a huge amount of game **content**, not just code.

For example:

* Sprite graphics
* Road graphics
* Background graphics
* Music samples
* FM instrument definitions
* Car animation frames
* Enemy car definitions
* Track segment data
* Color palettes
* Lookup tables
* Text

Imagine a ROM containing:

```
Sprite #152
  64×64 pixels
  Ferrari front-left frame 3
```

The C++ engine simply says:

```cpp
drawSprite(152);
```

It loads sprite #152 from the ROM.

Likewise, a road might be stored as:

```
Segment 0
  curvature = +3
  elevation = 0
  scenery = palm trees

Segment 1
  curvature = -2
...
```

The C++ engine interprets that data to build the road.

---

## Was *all* the code rewritten?

Almost.

Chris White spent years disassembling the original 68000 program and understanding every subsystem:

* Road generation
* Traffic AI
* Collision detection
* Timing
* Physics
* Camera
* Route branching
* Scoring
* Attract mode

Then he rewrote each subsystem in C++.

So instead of translating assembly instruction-by-instruction, he translated **behavior**.

---

## Why not just decompile?

Because 68000 assembly doesn't decompile neatly.

You lose:

* variable names
* class structure
* function names
* comments
* types

Reverse engineering becomes detective work:

> "This routine seems to calculate centrifugal force..."

then you write:

```cpp
void Car::updateCentrifugalForce(...)
```

The resulting code is vastly easier to understand than a literal decompilation.

---

This is why CannonBall is often cited as one of the best examples of **behavioral reimplementation**. It's closer to projects like OpenMW or OpenRCT2 than to an emulator: the engine is new, but it consumes the original game's asset files so it can faithfully reproduce the original experience without distributing Sega's copyrighted graphics, music, and other content.

[Reply Link](https://chatgpt.com/s/t_6a418e1b337c8191882dafa6633aa11b)

<hr/>

<font color=blue>

> At one location, the ROMs that I see include the following epr-10187.88 and others with the epr- prefix; mpr-10371.9 and others with the mpr- prefix and opr-10185.11 and others with the opr- prefix. I assume these were the standard part names and that each prefix indicates a particular module and CPU.

</font>

Exactly. Those prefixes are **Sega internal part-number designations**, not indicators of which CPU used the ROM. They describe **how the ROM chip itself was manufactured**. ([SMS Power!][1])

For *Out Run*, your examples decode like this:

* **EPR-xxxxx** = **EPROM**

  * Electrically Programmable Read-Only Memory.
  * UV-erasable chips used during development, location tests, service updates, and lower-volume production.
  * Example: `epr-10187.88`

* **MPR-xxxxx** = **Mask ROM**

  * Custom factory-produced ROM.
  * Cheapest for mass production once the game software was finalized.
  * Example: `mpr-10371.9`

* **OPR-xxxxx** = **One-Time Programmable ROM (OTP)**

  * Programmed once electrically, but not erasable.
  * Often used as a middle ground between EPROMs and expensive mask ROM production.
  * Example: `opr-10185.11` ([SMS Power!][1])

The suffix after the period is something different:

```
epr-10187.88
           ^^
```

That `.88` is the **PCB location** (silkscreen reference) where the chip sits on the board, not part of the Sega part number.

Likewise:

```
mpr-10371.9
          ^
```

means "install this ROM at location **9** on the PCB."

---

### They are not organized by CPU

One thing that confuses people is that MAME names the files exactly as they are labeled on the chips.

So you might see:

```
epr-10187.88
epr-10186.66
mpr-10371.9
opr-10185.11
```

Those chips can belong to completely different functional groups.

For example, an *Out Run* board contains ROMs for:

* Main 68000 program
* Secondary 68000 program
* Z80 sound program
* Character graphics
* Sprite graphics
* Road graphics
* PCM sound samples

Some are EPROMs, some are Mask ROMs, some OTPs—it simply depended on **how Sega manufactured that particular chip**, not what it contained.

---

### How emulators know which is which

The MAME driver (or CannonBall's ROM loader) has a table that says something like:

```text
Load epr-10187.88
    -> Main CPU ROM
    -> Address 0x00000

Load epr-10186.66
    -> Main CPU ROM
    -> Address 0x00001

Load epr-10183.26
    -> Sound CPU ROM

Load mpr-10371.9
    -> Sprite graphics

Load opr-10185.11
    -> Road graphics
```

So the filename itself doesn't tell you the function. The emulator's hardware definition does.

---

### Why there are so many ROMs

The original *Out Run* deluxe board is almost like a small computer with several independent memories. A simplified map looks like:

```
             Main 68000
          Program ROMs (EPR)

                 │
                 │
      -------------------------
      │                       │
Second 68000             Z80 Sound CPU
 Program ROMs             Program ROM

      │                       │
      │                       └── PCM Sample ROMs
      │
      ├── Sprite ROMs (MPR)
      ├── Road ROMs (OPR/MPR)
      ├── Tile ROMs
      └── Lookup/Timing PROMs
```

One of the reasons *Out Run*'s ROM set seems large compared to many 1986 arcade games is that **most of the ROMs aren't code at all**. The two 68000 CPUs and the Z80 together only use a fraction of the total ROM capacity. The majority of the chips store graphics and sampled audio, which is precisely why projects like CannonBall can replace all of the CPU code with C++ yet still require the original ROMs for the game's visual and audio assets.

[1]: https://www.smspower.org/Development/ROMPartNumbers?utm_source=chatgpt.com "ROM Part Numbers - Development - SMS Power!"

[Reply Link](https://chatgpt.com/s/t_6a418e3278448191a11dcc446aaf64b7)

<hr/>

<font color=blue>

> Is OutRun considered abandonware. I see a listing under that designation at some places.

</font>

"Abandonware" is more of a **community label than a legal status**.

For *Out Run*, the answer is **no, it is not legally abandonware**, even though many websites categorize it that way.

Here's why:

* Sega still exists and still owns the *Out Run* intellectual property.
* The original arcade game's code, graphics, music, and sound remain protected by copyright in most countries.
* There has never been a legal declaration that *Out Run* has entered the public domain or that Sega has relinquished its rights.

The term "abandonware" generally means:

> "Software that is no longer sold or officially supported, and whose copyright owner is not actively enforcing distribution."

That's a social convention, not a legal category.

### Why do abandonware sites host it?

Many sites make a practical argument:

* The original arcade hardware has been out of production for decades.
* Some ports are difficult or impossible to purchase legally.
* Sega has not consistently made every version available.

As a result, they label it "abandonware" and distribute ROMs. However, that doesn't mean the distribution is authorized.

### Complicating factors

*Out Run* is an interesting case because there are multiple versions with different rights situations.

For example:

* The original 1986 arcade game.
* Home ports for systems like the Master System, Genesis/Mega Drive, and others.
* Later re-releases and remakes.
* Versions that originally used Ferrari likenesses under license.

Over the years, licensing issues—particularly involving Ferrari—have sometimes affected whether Sega could re-release specific versions. This contributed to periods when *Out Run* disappeared from digital storefronts.

### CannonBall's approach

The CannonBall project avoids distributing Sega's copyrighted assets. Instead, it asks users to supply the original ROMs themselves. That's similar in spirit to projects like OpenMW or OpenRCT2, where the engine is open source but the original game content is still required.

### Practical reality

There's a distinction between legal status and what people commonly do:

* **Legally:** The *Out Run* ROMs are still copyrighted and aren't "abandonware" in any recognized legal sense.
* **Practically:** Many retro gaming communities refer to them as abandonware because they're old and have not always been commercially available, but that label doesn't change the copyright status.

So if you see *Out Run* on an "abandonware" site, it's best understood as the site's own categorization rather than an indication that the game has become free to copy or distribute.

[Reply Link](https://chatgpt.com/s/t_6a418e4561c48191ae4ef66064bf8dc3)

<hr/>

<font color=blue>

> A Mexico City to Buenos Aires race might be doable, without interruption, for flight-enabled vehicles and/or VTOLs, with the Panamanian segment possibly traversed off-shore in the air.

</font>

That's an interesting idea, and with aircraft it actually changes the nature of the challenge in a way that's analogous to how the original Cannonball differed from traditional racing.

For **road vehicles**, the Darién Gap is the showstopper. It's about 100 km (60 miles) of dense rainforest and wetlands with no completed highway. Every overland expedition has to either:

* ship the vehicle by sea,
* transport it by air,
* or undertake an extremely difficult off-road expedition that isn't practical for a timed race.

For **VTOL or STOL aircraft**, or roadable aircraft, the gap largely disappears as an obstacle. A competitor could drive to the Caribbean coast of Panama, take off, fly around or over the Darién region, land in Colombia, and continue by road.

That said, several other challenges would still dominate:

* **International aviation regulations.** Every border crossing becomes both a customs/immigration event and a flight-planning exercise. You'd need to comply with each country's aviation authority, file flight plans where required, and obtain any necessary clearances.
* **Fuel logistics.** Unlike a Ferrari, a light aircraft or VTOL can't assume fuel is readily available at every stop.
* **Weather.** Central America and the northern Andes often have convective storms, low cloud, and mountainous terrain that can delay or reroute flights.
* **Terrain.** The route south of Colombia passes near or through the Andes. Pilots would need to choose between high-altitude crossings or longer coastal routes.

It also raises an interesting design question: what are you trying to optimize?

* A **pure point-to-point record** ("fastest from Mexico City to Buenos Aires by any combination of driving and flying") would favor aircraft.
* A **roadable-aircraft challenge** would be more like an aviation version of the Cannonball, where the vehicle has to be capable of both modes without external transport.
* A **VTOL-only** event would resemble a long-range air rally more than an automotive endurance run.

As roadable aircraft become more practical, you could imagine a modern "trans-American Cannonball" that rewards route planning, weather judgment, border logistics, and energy management as much as outright speed. In that sense, it would echo the original 1970s Cannonball, where the fastest teams weren't simply the ones with the most powerful cars—they were often the ones that managed fuel stops, navigation, traffic, and police avoidance most effectively.

[Reply Link](https://chatgpt.com/s/t_6a418f74241481918ffbf43dab8c6168)

<hr/>

<font color=blue>

> The rules would have to place restrictions: roadable ultralights or VTOL's, air-borne travel only permitted around the gap in Panama and maybe in a select range of other segments, but nowhere else.

</font>

That would make it much closer in spirit to the original Cannonball: the aircraft capability would be a **constraint-driven tool** rather than the primary means of travel.

A ruleset could look something like this:

* The vehicle must be a single, self-contained machine that starts and finishes under its own power.
* No support vehicles or transport by truck, ship, or cargo aircraft.
* The vehicle must be legal (or at least eligible) to operate on public roads in the countries traversed.
* Airborne operation is permitted only within designated "air corridors" established by the organizers.
* Outside those corridors, all travel must be on public roads.
* All border crossings would have to comply with customs, immigration, and aviation regulations.

The **Darién Gap** would be the obvious mandatory flight corridor. Others might exist where there simply isn't a practical continuous road or where organizers wanted to showcase the dual-mode capability of the vehicles.

Such restrictions would keep the emphasis on:

* Efficient road performance.
* Fast transitions between driving and flying.
* Route planning.
* Reliability.
* Fuel and energy management.

Rather than rewarding the fastest airplane.

In some ways, it would resemble a hybrid of a grand touring rally and an aviation challenge. The engineering trade-offs become particularly interesting:

* A better wing or rotor system usually adds drag and weight on the road.
* Better road suspension often increases weight, reducing flight performance.
* Fuel capacity helps both modes but increases takeoff weight.
* Folding-wing or tilting-rotor mechanisms add complexity and maintenance demands.

Those compromises are reminiscent of events like the DARPA Grand Challenge, where the contest is as much about systems engineering as raw performance.

One practical issue is that even with restricted flight segments, organizers would likely need to coordinate with multiple national aviation authorities and road authorities. Unlike the largely unofficial 1970s Cannonball runs, a transcontinental event involving aircraft would be difficult to conduct informally because every takeoff, landing, and international air crossing falls under aviation regulations.

From an engineering perspective, though, it would be a fascinating proving ground for emerging roadable aircraft and eVTOL concepts. A vehicle that could complete thousands of kilometers on highways, then seamlessly bypass a major geographic barrier like the Darién Gap under its own power, would demonstrate a level of versatility that no conventional car or light aircraft can match on its own.

[Reply Link](https://chatgpt.com/s/t_6a418f8762788191b57246fadaa8085a)

<hr/>

<font color=blue>

> I noticed a few other details in the games, too: some of the OutRun game's endings have bad things happening to the driver; and the OutRunner game has a few cases of female drivers with male passengers or a burly male driver and passenger.

</font>

Those are both good observations, and they reflect some of Sega's quirky design choices in the series.

In **Out Run**, the multiple endings were one of the game's signature features. Depending on which of the five destination routes you reached, you got a different animated ending. They weren't all triumphant:

* Some endings show the couple celebrating.
* Some are humorous or bittersweet.
* A few involve the Ferrari being damaged or breaking apart in slapstick fashion.
* One of the more memorable endings has the car stopping suddenly and the passenger walking off, leaving the driver looking dejected.

The endings are intentionally cartoonish rather than realistic, fitting the game's lighthearted tone.

**OutRunners** took that sense of humor even further. Instead of one anonymous couple, it features several teams with exaggerated personalities, each driving a distinctive vehicle. Sega clearly wasn't aiming for realism—they were creating colorful, almost comic-book characters.

That includes teams where:

* The driver is a woman and the passenger is a man.
* Both occupants are large, muscular men.
* Other pairings play with stereotypes or visual contrasts.

This was somewhat unusual for racing games in 1992. Many games of the era defaulted to a male driver with a female passenger (as in the original *Out Run*), whereas *OutRunners* broadened the cast considerably. The game doesn't make a big point of these combinations; they're simply part of the diverse roster.

The shift also reflects the game's overall design philosophy. Whereas the original *Out Run* was about the fantasy of a romantic drive through scenic landscapes, *OutRunners* is closer to an ensemble adventure. Each team has its own visual identity and ending, making the characters as much a part of the experience as the driving.

It's one of the reasons *OutRunners* has a dedicated following today. While it never achieved the iconic status of the original, its larger cast, branching routes, multiplayer focus, and playful humor gave it a personality that stood out among early 1990s arcade racers.

[Reply Link](https://chatgpt.com/s/t_6a4190730c9481918fba2eb9ece2fc98)

<hr/>

<a name=session2></a>
# The Addressing And Layout Of The ROMs

<hr/>

<font color=blue>

> In the decompilation of the OutRun arcade game, multiple ROMs were involved, with names prefixed by epr-*, mpr-* and opr-*. How were they addressed, on what CPU's and where were the addresses of them determined?

</font>

The ROM prefixes in Sega arcade boards from the mid-1980s are primarily **part-number conventions**, not indicators of CPU address space. For **OutRun** (System 16-derived "OutRun hardware"), the ROMs are connected to different buses depending on their function, and the memory map is defined by the board wiring and the software's linker layout.

Here's how the three prefixes were generally used:

* **EPR-xxxxx** ("EPROM")

  * Usually contains executable program code or small tables.
  * Connected directly to a CPU's program bus.
  * These are the ROMs you primarily decompile.

* **MPR-xxxxx** ("Mask Program ROM")

  * Factory mask ROMs.
  * Typically hold graphics, road data, sprites, PCM samples, etc.
  * Usually not CPU instruction streams.

* **OPR-xxxxx**

  * Another Sega mask ROM numbering series, commonly used for graphics, lookup tables, or sound data depending on the board.

The prefixes themselves do **not** tell you where they appear in memory.

### CPUs in OutRun

OutRun uses multiple processors:

* Main Motorola 68000 (game logic)
* Sub Motorola 68000 (road/object assistance)
* Z80 (sound)
* Dedicated Sega graphics hardware
* Sega PCM sound hardware ([Museum of the Game][1])

Each processor has its own address space.

## Main 68000 program ROM

The EPR ROMs containing the game code are connected to the main 68000's 24-bit address bus.

Because the 68000 has a **16-bit data bus**, ROMs are paired:

* one ROM supplies even bytes
* one ROM supplies odd bytes

For example:

```
0x000000 even -> EPR A
0x000001 odd  -> EPR B
```

Then another pair occupies the next block.

In MAME you'll see definitions like

```cpp
ROM_REGION(0x60000, "maincpu", 0)

ROM_LOAD16_BYTE("epr-10380.133", 0x000000, 0x10000, ...)
ROM_LOAD16_BYTE("epr-10382.118", 0x000001, 0x10000, ...)

ROM_LOAD16_BYTE("epr-10381.132", 0x020000, ...)
ROM_LOAD16_BYTE("epr-10383.117", 0x020001, ...)
```

Those offsets are **not stored inside the ROM**; they describe how the physical chips are wired into the CPU's address space. ([Museum of the Game][1])

## Sub 68000

The second 68000 has its own independent ROM region.

It also executes EPR ROMs mapped beginning at address 0 of *its own* address space.

The two 68000s communicate through shared RAM and hardware registers rather than sharing a single ROM image.

## Z80

The Z80 has a completely separate 64 KiB address space.

Its program resides in another EPR ROM.

The Z80 accesses:

* its own program ROM
* RAM
* YM2151
* Sega PCM

through its own memory map.

## Graphics ROMs

The MPR/OPR ROMs are generally **not executed**.

Instead they are connected directly to custom Sega graphics ASICs.

Examples include:

* sprite graphics
* tile graphics
* road graphics
* road lookup tables

The graphics hardware generates addresses into these ROMs while rendering each frame.

The CPUs typically don't "run" code from them.

## PCM ROMs

PCM sample ROMs (often MPR/OPR parts) are connected directly to the Sega PCM chip.

The Z80 writes playback commands; the PCM hardware fetches sample bytes itself.

## Where are the addresses determined?

There are three levels:

### 1. PCB wiring

The ROM chips are physically connected to address and data lines.

For example:

```
68000 A1-A17
        |
        +------> EPROM address pins
```

Chip-select logic decides which ROM responds to a given address.

This determines that, for example,

```
000000-01FFFF
```

is program ROM.

### 2. ROM loading (emulators/decompilation)

MAME encodes the physical layout with declarations such as

```cpp
ROM_LOAD16_BYTE(...)
```

which specify

* which ROM
* even/odd byte lane
* starting address
* size

These declarations mirror the original PCB wiring rather than information embedded in the ROMs themselves. ([Museum of the Game][1])

### 3. The linker

When Sega built OutRun, the linker generated code assuming fixed addresses.

For example,

```
JSR $1234
```

assumes the routine lives at that address in the 68000 memory map.

Nothing inside the ROM says "load me at 0x20000"; the ROM image is simply a sequence of bytes. The mapping comes from the hardware design and the build process.

## How does a decompilation discover this?

Projects like the OutRun decompilation typically begin with:

1. The MAME ROM definitions (showing where each chip is mapped).
2. The PCB schematics, when available.
3. The 68000 reset vector at address 0, which points to the initial stack pointer and program counter.
4. Disassembly of the ROMs at those mapped addresses.

Once the ROMs are placed into the correct address space, every absolute jump, subroutine call, interrupt vector, and data reference resolves correctly, allowing the original program structure to be reconstructed.

In short, the ROM prefixes (EPR, MPR, OPR) identify the *type* of ROM Sega used, but the addresses come from the **hardware memory map** (PCB wiring), reflected in emulator ROM definitions and assumed by the software at link time—not from metadata stored inside the ROM chips themselves.

[1]: https://www.arcade-museum.com/tech-center/machine/outrun?utm_source=chatgpt.com "Museum of the Game - International Arcade Museum & Killer List of Videogames: Arcade, Videogame, Pinball Machine, and Antique Coin-Operated History | Museum of the Game"

[Reply Link](https://chatgpt.com/s/t_6a5ac8dd196881918998f468e1b3f783)

<hr/>

<a name=session3></a>
# Fixing A Hidden Character Code Bug

<hr/>

<font color=blue>

> I found a hidden inconsistency in one of the source code files I'm reviewing and fixing that comes from the under-the-hood encoding that the operating system does on files to distinguish between ASCII text files and UTF-8 text files. The main implementation for the code is Windows, but it's distributed for other platforms, including Linux. One of the C++ files, in it is encoded as a text file, but has a character constant in the range 0x80-0xff: character 0xa9. It compiles consistently under g++ on Linux. However, when the file is remade as UTF-8 form, by virtue of some of the other characters (in comments) remade as UTF-8, the constant is treated as a "multi-character constant" because the file format forces the 0xa9 encoding as the multi-byte form, I assume, because it's outside the 0x00-0x7f range.

</font>

Yes. What you're seeing is a real consequence of how source file encoding interacts with C++ translation phases.

The important distinction is that the compiler doesn't read "bytes" directly as character literals. It first interprets the source file according to its source character encoding, and *then* parses tokens like character literals.

In your original file:

* The file is effectively a single-byte encoding (perhaps Windows-1252, ISO-8859-1, or simply "8-bit text").
* The byte

```text
A9
```

appears inside

```cpp
'\xA9'   // or perhaps '©' if written literally
```

or perhaps just

```cpp
'©'
```

If the compiler assumes a single-byte code page where byte `0xA9` represents one character, then the character literal contains exactly one character.

When the file is converted to UTF-8, that same character becomes two bytes:

```text
C2 A9
```

because U+00A9 COPYRIGHT SIGN is encoded in UTF-8 as

```
0xC2 0xA9
```

Now the compiler has to interpret those bytes according to the source encoding.

### Why it becomes a multicharacter constant

Suppose the source literally contains

```cpp
'©'
```

In a UTF-8 source file, the compiler sees a character whose UTF-8 representation occupies two bytes.

Whether `'©'` is considered a valid ordinary character literal depends on:

* the C++ standard version,
* the compiler,
* the source character set,
* the execution character set,
* compiler options like GCC's `-finput-charset` and `-fexec-charset`.

Older compiler modes—and some implementations even today—essentially tokenize the bytes inside the literal rather than treating them as one abstract Unicode code point. The bytes

```
C2 A9
```

look like two characters, so

```cpp
'©'
```

becomes equivalent to

```cpp
'\xC2\xA9'
```

which is a multicharacter literal.

GCC will typically warn:

```
warning: multi-character character constant
```

because it contains two encoded code units.

### Why Linux "worked" before

The file wasn't actually UTF-8.

It was probably being interpreted as Latin-1 or Windows-1252, where

```
A9
```

is one byte representing ©.

So

```
'©'
```

was one character.

After conversion, the file physically contains

```
C2 A9
```

which changes what the lexer sees.

### The portable solution

If the intent is the numeric value 0xA9, don't rely on the source encoding at all.

Instead write

```cpp
'\xA9'
```

or

```cpp
static_cast<char>(0xA9)
```

depending on what the code is actually trying to express.

Those forms survive:

* ASCII source
* UTF-8 source
* UTF-16 source
* Windows-1252 source
* source control conversions
* editor encoding changes

because the bytes representing the source file are no longer significant.

### One subtlety

You mentioned "the operating system distinguishes ASCII from UTF-8."

Strictly speaking, operating systems generally do **not** do this. Windows, Linux, and macOS mostly treat source files as arbitrary byte streams. It's the **editor**, **version control system**, or **compiler** that decides how to interpret those bytes.

For example:

* Notepad may detect UTF-8 (especially via a BOM or UTF-8 validity heuristics).
* Visual Studio may assume UTF-8 or the current Windows code page depending on settings and BOM.
* GCC uses options such as `-finput-charset=` to determine how to decode source files.
* Clang has similar source encoding handling.

So the behavior changes because the compiler is now decoding the source as UTF-8 rather than as a single-byte encoding.

From your description, this sounds exactly like the kind of latent portability bug that often surfaces when a project is modernized to UTF-8. A literal non-ASCII character in source code is inherently dependent on the source encoding; replacing it with an escape sequence like `'\xA9'` (or, if Unicode semantics are intended, `u'\u00A9'` or `U'\U000000A9'` as appropriate) removes that dependency.

[Reply Link](https://chatgpt.com/s/t_6a73d4390cb48191b17dc4fd8ebe83c3)

[Ad: Plural | AI For DevOps - Plural Labs, Inc.](https://www.plural.sh/?oppref=gAAAAABqc8EIYnPHQXTGjSudLmSoXbStvLIs6u04m-k1xJQwK8Q7TmdFPD-aORVgA_x-zXsBy4RaVwixjog1Nq_EFhtZ_VArh8Qe1DsUPJazEtxp9zJDS60w&olref=gAAAAABqc8EI5cR4jv3k8_TLTeWGHcT7wYhhyMyA9EITWeNSv0B8oDfbk_NK15ILEldNYlVz2cwQyV3UFDkgnUtDL39lAC3up5BAUdLaO78mJIPmKekmTPFcwg7wkCXRSlCcovkI1hKzPW8RMT7lyPvJF_AYOX8CjAw)

<hr/>

<font color=blue>

> What would happen if it were written as static_cast<char>('©')?

</font>

That depends on how `'©'` is interpreted **before** the `static_cast` is applied.

The cast itself doesn't solve the encoding issue—it only converts whatever value the character literal already has to `char`.

There are two main cases:

### Case 1: Single-byte source encoding

If the source is interpreted as Windows-1252 or ISO-8859-1, then

```cpp
static_cast<char>('©')
```

is equivalent to

```cpp
static_cast<char>(0xA9)
```

(or possibly `-87` if `char` is signed, though the underlying bit pattern is still `0xA9`).

This behaves as intended.

### Case 2: UTF-8 source where `'©'` becomes a multicharacter literal

If the compiler treats

```cpp
'©'
```

as the two-byte sequence

```text
0xC2 0xA9
```

then it becomes a multicharacter literal. For GCC and Clang, multicharacter literals have type `int`, and their value is implementation-defined.

For example,

```cpp
'©'
```

might evaluate to something like

```cpp
0xC2A9
```

or another implementation-defined integer value.

Then

```cpp
static_cast<char>('©')
```

simply truncates that integer to eight bits:

```cpp
static_cast<char>(0xC2A9)
```

becomes

```cpp
(char)0xA9
```

on a little-endian target where the low byte is retained.

So **by coincidence**, you may still get the value `0xA9` on many compilers.

### But that's not portable

The C++ standard deliberately leaves the value of a multicharacter literal implementation-defined.

So another compiler could choose a different packing:

* `0xA9C2`
* some other representation
* or even reject it outright.

The cast would then produce a different result.

### The safe alternatives

If your intent is "the byte value `0xA9`", write exactly that:

```cpp
static_cast<char>(0xA9)
```

or

```cpp
'\xA9'
```

If your intent is "the Unicode copyright sign", use a Unicode character literal:

```cpp
u'\u00A9'
```

or

```cpp
U'\U000000A9'
```

Those represent the Unicode code point regardless of the source file encoding, although you'll still need to consider how that value is converted if you eventually store it in a plain `char`.

So `static_cast<char>('©')` doesn't eliminate the underlying problem. It merely casts whatever value the compiler has already assigned to `'©'`, and if that literal has become a multicharacter constant due to UTF-8 encoding, the result is still implementation-defined.

[Reply Link](https://chatgpt.com/s/t_6a73d47a45148191921ff2a09b8b1734)

<hr/>

<font color=blue>

> The copyright sign is what's intended. It's using the value to compare to what characters are being read in as a messaae string that will be put out on a diagnostic display.

</font>

That changes the recommendation somewhat, because now the key question is **what encoding is the message string being read in?**

There are two possibilities.

### If the message is an 8-bit encoded string (Windows-1252, Latin-1, etc.)

Then the comparison is really against the byte value `0xA9`.

For example:

```cpp
char ch = *p;

if (ch == '\xA9')
    ...
```

or

```cpp
if (static_cast<unsigned char>(ch) == 0xA9)
    ...
```

is exactly what you want. In this case, comparing against the Unicode code point U+00A9 would actually be the wrong abstraction, because you're processing encoded bytes, not Unicode characters.

### If the message is UTF-8

Then the copyright sign is **not one `char`**.

UTF-8 encodes U+00A9 as

```text
C2 A9
```

So if you're iterating through a `char*` or `std::string`, you'll see two successive bytes:

```cpp
0xC2
0xA9
```

Neither byte is "the copyright sign." Comparing one `char` against `'©'` (or `'\xA9'`) won't correctly identify the character.

Instead, you'd need to decode UTF-8 into Unicode code points first, or explicitly recognize the two-byte sequence.

### Your original observation suggests...

...that this code was written assuming a single-byte character encoding, and converting the source file to UTF-8 merely exposed that assumption.

A question I'd ask is: **What encoding are the diagnostic messages themselves in?**

* If they're stored in a `.cpp` string literal, converting the source file to UTF-8 may also have changed those strings to UTF-8.
* If they're loaded from a resource file or external text file, that file's encoding determines what bytes the code sees.

If both the source file and the message data were historically Windows-1252, then the code was internally consistent. Converting only the source file to UTF-8 while leaving the logic unchanged introduces exactly the inconsistency you found.

So this may be more than just fixing a character literal—it may require deciding whether the project is:

* remaining an 8-bit encoded application (in which case `'\xA9'` is appropriate), or
* moving to UTF-8 end-to-end (in which case the parsing logic needs to operate on decoded Unicode code points rather than individual `char` values).

One thing that caught my attention is that **g++ on Linux compiled the original code consistently**. That suggests the runtime data is probably still expected to be a single-byte encoding. If the messages had already been UTF-8, I'd expect the code comparing one `char` to the copyright sign to have been malfunctioning even before the source file was converted. That makes me suspect you've uncovered an assumption that the data and the source file would always use the same 8-bit encoding.

[Reply Link](https://chatgpt.com/s/t_6a73d48f363881919f5359c5fc7f68b7)

[Ad: Expert-Led... 95% Manual Testing. Now Lead... - Packetlabs Ltd.](https://www.packetlabs.net/?utm_source=chatgpt&utm_medium=paid_ai&utm_campaign=best_pentest_provider_usa&oppref=gAAAAABqc8RGdc9USWf4JRUf052vPZxu_Sw45NUa09xqneteP4d9pxOb1HsytcfzSjQDGiy2oirtCO94Vfi-FYdoM-KDVfmyF_ISF9M2Zj3Gcd0_B7y9Xhsw&olref=gAAAAABqc8RG5Y5qO_34j-mV9gFL_ctrxzn2SYzqJAHHwbWso-IOC75w-MgbuScD10wLweIbFrP7EfBio-tO5jqRwIq9LBMGRSGLYzg1-QzlzuV8wmxFlx2y0NVWMClj_HfqVDSuTa033LFTE7uTWYm_DsUWhZqDlww)

<hr/>

<font color=blue>

> I did a global check. All string constants that go through this routine involve only characters 0x00-0x7f in them. All non-constant strings that go into the routine come out of c_str().

</font>

That additional information is important. It strongly suggests that the routine is **not actually doing Unicode text processing**; it is processing an 8-bit string where the copyright sign is a special case.

The fact that:

* all literal strings passed to the routine are strictly `0x00–0x7F`, and
* dynamic strings arrive through `c_str()` (which only gives you the underlying bytes of a `std::string`),

means the routine has no UTF-8 awareness unless something else upstream is doing conversion.

A `std::string` is just a sequence of bytes. `c_str()` does not convert encoding. If a caller has:

```cpp
std::string s = "...";
routine(s.c_str());
```

then the routine receives exactly the bytes stored in `s`.

So the real question is: **what byte value does the message source use for the copyright sign?**

If it is a Windows diagnostic display path, there is a good chance it is historically using an ANSI code page (often Windows-1252), where:

```
© = byte 0xA9
```

In that environment, the comparison should probably be against the byte:

```cpp
static_cast<unsigned char>(ch) == 0xA9
```

or:

```cpp
ch == '\xA9'
```

rather than against a source character literal.

The reason I would avoid:

```cpp
static_cast<char>('©')
```

in this situation is that it expresses the wrong thing. It says:

> "Take a C++ source character that represents the Unicode copyright character, then squeeze it into an 8-bit char."

But your code's actual requirement appears to be:

> "Detect the byte value used by this 8-bit diagnostic message encoding."

Those are different concepts.

A robust version would be something like:

```cpp
if (static_cast<unsigned char>(ch) == 0xA9)
{
    ...
}
```

The `unsigned char` matters if `char` is signed on the target. On many Linux x86 builds, plain `char` is signed, so a byte `0xA9` may appear as `-87`. Comparing through `unsigned char` avoids that ambiguity.

If you are moving the source files to UTF-8 but **not** changing the diagnostic string data format, then replacing the source literal with `0xA9` is likely the correct surgical fix.

One other possibility worth checking: if this diagnostic display ultimately uses a Windows API such as the `A` (ANSI) variants, then `0xA9` is very likely the intended byte. If it uses the `W` (wide-character) variants or UTF-8 conversion layers, then the right representation would be U+00A9 instead. The `c_str()` clue makes me lean toward the former.

[Reply Link](https://chatgpt.com/s/t_6a73d4d0c970819188c8769b0c8a15b4)

<hr/>

<font color=blue>

> Most of the non-constant use-cases come from "char" and "int", passing through std::stringstream into std::string, e.g. int i gets passed into std::stringstream ss as ss << i, and the result gets passed into std::string as ss.str(). The ultimate sources are definitely meant to be 8-bit character strings, and I don't see any place where anything outside the range 0x00-0x7f is actually used.

</font>

That makes the picture much clearer.

From what you've described, this routine is fundamentally an **8-bit byte-oriented formatter/parser**, not a Unicode text processor.

The pipeline looks like:

```
char/int/etc.
        ↓
std::stringstream
        ↓
std::string
        ↓
c_str()
        ↓
this routine
```

For integers, `stringstream` only emits ASCII digits (`'0'`–`'9'`), plus perhaps `'-'` or `'+'`. For `char`, unless callers are deliberately inserting bytes ≥ 0x80, only ASCII is produced. `std::string` and `c_str()` simply preserve those bytes.

So if you've verified that:

* all string literals are ASCII-only,
* all generated strings are ASCII-only,
* there are no other callers supplying extended characters,

then the comparison against the copyright sign is almost certainly a dead or nearly dead code path.

That raises two possibilities:

1. **Legacy compatibility.** At one point the routine may have processed text that included a copyright symbol in an 8-bit encoding, but today's code no longer generates such strings.

2. **Defensive coding.** The author anticipated external input that might contain `0xA9`, even if none of the current callers do.

Either way, the comparison is really about the byte value `0xA9`, not about Unicode.

Given that, I'd consider changing

```cpp
'©'
```

to

```cpp
'\xA9'
```

or, even more explicitly,

```cpp
static_cast<unsigned char>(ch) == 0xA9
```

if `ch` is a `char`.

The latter has the advantage of making the intent obvious:

> "I'm comparing the incoming byte against the value 0xA9."

It also avoids any dependence on:

* the source file encoding,
* compiler interpretation of non-ASCII source characters,
* whether `char` is signed or unsigned.

One thing I find interesting is that your investigation has effectively shown this isn't just an encoding bug. It's a mismatch between **the representation in the source code** and **the abstraction the code is operating on**. The code operates on bytes, so expressing the special case as a byte value (`0xA9`) is a better fit than embedding a non-ASCII character literal in the source. That makes the code more robust even if the project later standardizes on UTF-8 source files.

[Reply Link](https://chatgpt.com/s/t_6a73d4e772108191b218851b1fe57fa9)

<hr/>

<font color=blue>

> I found the use case: the "About" screen.

</font>

That makes perfect sense.

The "About" screen is exactly the place where a copyright symbol would naturally appear, and historically it was very common for applications to store that text as an 8-bit string containing the single byte `0xA9`.

So your earlier observations now fit together:

* Most of the routine only ever sees ASCII.
* The one legitimate non-ASCII case is the About box.
* The code was written assuming an 8-bit encoding where `0xA9` represents ©.
* Converting the source file to UTF-8 changed the **source representation** of `'©'`, even though the runtime data model remained 8-bit.

In other words, the routine is comparing **encoded bytes**, not abstract Unicode characters. That makes a comparison like

```cpp
static_cast<unsigned char>(ch) == 0xA9
```

or

```cpp
ch == '\xA9'
```

a better expression of the intent than

```cpp
ch == '©'
```

because it decouples the code from the encoding of the source file.

One thing I'd still check is how the About text itself is constructed.

* If it's literally something like `"Copyright \xA9 1998..."`, then everything is consistently 8-bit.
* If it's `"Copyright © 1998..."` in a UTF-8 source file, then the string now contains the UTF-8 byte sequence `0xC2 0xA9`, and the routine will see two bytes instead of one. In that case, simply fixing the character literal won't be enough—the About string itself will also have changed representation.

Since you've already traced the use case, it's worth looking at that specific string. It will tell you whether the application is still operating on an 8-bit copyright byte or whether the source conversion has inadvertently converted the data to UTF-8 as well.

[Reply Link](https://chatgpt.com/s/t_6a73d4fbcde081919692eacde5ac5ec8)

<hr/>

<font color=blue>

> It would seem that the most portable way is to replace the embedded © in the character constant used by the About routine by '\xa9', and to also replace the reference to the character by '\xa9' in the function call where the string is used.

</font>

I think that's a reasonable approach **if the About string is intended to remain an 8-bit encoded string**.

For example, if the code currently has something like:

```cpp
if (ch == '©')
    ...
```

and

```cpp
About("Copyright © 2026");
```

then changing those to:

```cpp
if (static_cast<unsigned char>(ch) == 0xA9)
    ...
```

and

```cpp
About("Copyright \xA9 2026");
```

keeps the runtime representation exactly the same—a single byte `0xA9`—regardless of whether the source file is encoded as ASCII, Windows-1252, UTF-8, or something else.

The one caveat I'd mention concerns the string literal. In C and C++, `\x` escapes consume **as many following hexadecimal digits as possible**. So:

```cpp
"\xA92026"
```

does **not** mean `0xA9` followed by `"2026"`; it is parsed as one long hexadecimal escape. Your example has a space after the copyright symbol, so:

```cpp
"Copyright \xA9 2026"
```

is perfectly safe because the space terminates the escape. If the next character were a hex digit (`0`–`9`, `A`–`F`, `a`–`f`), you'd need to separate it, for example:

```cpp
"\xA9""2026"
```

or

```cpp
std::string("\xA9") + "2026"
```

if appropriate.

Given everything you've investigated, I also like this change because it documents the code's actual contract: **the routine is working with an 8-bit encoding**, not Unicode code points. Using `'\xA9'` makes that explicit and removes the dependency on how the compiler interprets non-ASCII characters in the source file.

[Reply Link](https://chatgpt.com/s/t_6a73d51265e88191b73684c4ca52cf47)

<hr/>
</font>
