# DogOystercatcherDyn - A Spatially-Explicit Individual-Based Model 

A simulation exploring how on-leash vs. off-leash dogs affect Eurasian Oystercatcher populations in urban green spaces.

> **Author**: Alyssa Weber (MSc Forest and Ecosystem Sciences, Göttingen)  

---

## Research Question

How does dog predation impact Eurasian Oystercatcher populations in urban green areas — and how does this differ when dogs are on-leash vs. off-leash?

---
## About the Eurasian Oystercatcher (Haematopus ostralegus)

- **Ecology**: Ground-nesting shorebird that has adapted to inland urban environments.
- **Breeding**: Lifelong monogamous pairs; return to same nesting site annually.
- **Lifespan**: ~13.7 years in the wild.
- **Maturity**: Reach sexual maturity at ~3 years.
- **Nesting**: Both parents care for eggs and chicks; strong parental defense.
- **Threats**: Habitat loss, human disturbance, and predation by urban predators.
- **Population Trend**: Declined ~40% over the past three generations.

> In cities, they rely on parks and green spaces for nesting — making them vulnerable to dog activity.

---

## About Dogs in Urban Environments

- **Leash Status**: On-leash dogs are more controlled; off-leash dogs have greater freedom and spotting range.
- **Prey Drive**: Varies by breed and individual — modeled as "high" or "low" in the simulation.
- **Predation Behavior**: 
  - Off-leash dogs have larger spotting radius and higher hunting interest.
  - All dogs may eat eggs or chicks if found (food-seeking behavior).
- **Human Control**: Owners are assumed to have more influence over on-leash dogs.
- **Urban Impact**: Dogs are a major source of disturbance for ground-nesting birds.

> This model focuses on dogs as a key urban predator — but future versions may focus on including cats and corvids.


## Model Overview

Simulates a 7-year breeding cycle of **Eurasian Oystercatchers** (ground-nesting birds) in a managed urban park (inspired by Eilenriede Wald, Hannover). Includes **dogs** with varying prey drive levels and leash status, modeling their impact on adult birds, chicks, and eggs.

### Key Features:
- **Spatially explicit**: 2m × 2m pixel resolution
- **Temporal grain**: 1 day (7 years = 2,555 days)
- **Agents**: Oystercatchers (with mates, nests, age, and parental care) and dogs (on/off-leash, high/low prey drive)
- **Predation mechanics**: Spotting → interest → pursuit → success (stochastic)

---

## UI Parameters 

| Parameter | Default | Description |
|--------|--------|-------------|
| Initial Oystercatchers | 20 | Must be even (for mate pairing) |
| Initial Dogs | 15 | Number of dogs entering park daily |
| On-Leash Dogs (%) | 50% | Proportion of dogs on leash |
| High Prey Drive Dogs (%) | 30% | Proportion with higher hunting tendency |
| Scenario | Standard | Predefined configurations (e.g., "Strict Leash Policy") |

> ⚠️ *Note: Some parameters (e.g., predation chance) are hardcoded and not exposed in UI.*

---

## Outputs

- **Live Oystercatcher population graph** (over time)
- **Spatial map** showing nests, individuals, and dog movement paths
- **Reporters**: live eggs, chicks, adults, predation events

---

## ⚠️ Important Note: This Model Is Not Yet Ready for Practical Use

This is a **foundational, conceptual model** — not a validated or policy-ready tool.

### Key Limitations:
- No cats, corvids, or other urban predators
- No migration, refuges, or intraspecies competition
- No real-world data calibration or validation
- Simplified dog behavior and bird life history
- No environmental variation

> **Purpose**: To explore ecological principles and inform future model development — **not to guide policy or management today**.

---

## Future Directions

1. **Add other predators** (cats, corvids) to compare threat levels
2. **Include refuge zones** (safe nesting areas) to test conservation strategies
3. **Model migration** and seasonal movement
4. **Add resource competition** and territory dynamics
5. **Validate with field data** from urban bird surveys
6. **Simulate policy scenarios** (e.g., "off-leash days per week")

---

## Try It Out for Yourself

Simply clone this repository, then open and run the model in QtCreator!

