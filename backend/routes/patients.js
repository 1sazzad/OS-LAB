const express = require("express");
const router = express.Router();
const Patient = require("../models/Patient");
const authMiddleware = require("../middleware/authMiddleware");

router.get("/", authMiddleware(["admin", "assistant"]), async (req, res) => {
  try {
    const patients = await Patient.find();
    res.json(patients);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

router.get("/profile", authMiddleware(["patient"]), async (req, res) => {
  try {
    const patient = await Patient.findOne({ userId: req.user.id });
    res.json(patient);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

module.exports = router;
